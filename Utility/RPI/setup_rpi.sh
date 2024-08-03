#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

# Variables
RASPI_IMAGE_URL="https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2024-07-04/2024-07-04-raspios-bookworm-arm64.img.xz"
IMAGE_FILE="2024-07-04-raspios-bookworm-arm64.img"
IMAGE_PATH="${SCRIPT_DIR}/2024-07-04-raspios-bookworm-arm64.img"
IMAGE_XZ_PATH="${SCRIPT_DIR}/2024-07-04-raspios-bookworm-arm64.img.xz"

LINUXKERNEL_URL="https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.20.tar.xz"
KERNEL_DIR="linux-6.6.20"
KERNEL_PATH="${SCRIPT_DIR}/linux-6.6.20-image"
KERNEL_XZ_PATH="${SCRIPT_DIR}/linux-6.6.20.tar.xz"

MOUNT_DIR="/mnt/rpi"
USERNAME="pi"
PASSWORD_HASH=$(openssl passwd -6 "pi")

# Print all variables
echo -e "[!] Variables:"
echo -e "\tRASPI_IMAGE_URL: ${RASPI_IMAGE_URL}"
echo -e "\tIMAGE_FILE: ${IMAGE_FILE}"
echo -e "\tIMAGE_PATH: ${IMAGE_PATH}"
echo -e "\tIMAGE_XZ_PATH: ${IMAGE_XZ_PATH}"
echo -e "\tLINUXKERNEL_URL: ${LINUXKERNEL_URL}"
echo -e "\tKERNEL_DIR: ${KERNEL_DIR}"
echo -e "\tKERNEL_PATH: ${KERNEL_PATH}"
echo -e "\tKERNEL_XZ_PATH: ${KERNEL_XZ_PATH}"
echo -e "\tMOUNT_DIR: ${MOUNT_DIR}"
echo -e "\tUSERNAME: ${USERNAME}"
echo -e "\tPASSWORD_HASH: ${PASSWORD_HASH}\n"

# Update and install necessary packages
echo -e "[!] Updating and installing necessary packages...\n"
sudo apt update
sudo apt upgrade -y
sudo apt-get install -y qemu qemubuilder qemu-system-gui qemu-system-arm qemu-system-data qemu-system qemu-utils qemu-efi openssl openssh-server g++ gcc tar build-essential cmake unzip git python pkg-config rsync wget gcc-aarch64-linux-gnu g++-aarch64-linux-gnu

# Check if the image exists
if [ -f "${IMAGE_PATH}" ]; then
    IMAGE_ALREADY_EXISTS=true
    echo -e "[!] Image already exists at ${IMAGE_PATH}. Skipping..."
else
    IMAGE_ALREADY_EXISTS=false
    # Check if the image file exists
    if [ -f "${IMAGE_XZ_PATH}" ]; then
        echo -e "[!] Image XZ file already exists at ${IMAGE_XZ_PATH}. Skipping download...\n"
    else
        # Download Raspberry Pi OS image
        echo -e "[!] Downloading Raspberry Pi OS image...\n"
        wget ${RASPI_IMAGE_URL}
    fi
    echo -e "[!] Uncompressing the image...\n"
    unxz ${IMAGE_XZ_PATH}
fi

# Check if kernel exists at the specified path
if [ -f "${KERNEL_PATH}" ]; then
    KERNEL_ALREADY_BUILT=true
    echo -e "[!] Kernel already exists at ${KERNEL_PATH}. Skipping...\n"
else
    KERNEL_ALREADY_BUILT=false
    # Check if the kernel file exists
    if [ -f "${KERNEL_XZ_PATH}" ]; then
        echo -e "[!] Kernel XZ file already exists at ${KERNEL_XZ_PATH}. Skipping download...\n"
    else
        # Download and build the Linux kernel for qemu arm64
        echo -e "[!] Downloading and building the Linux kernel for qemu arm64...\n"
        wget ${LINUXKERNEL_URL}
    fi
    tar xvJf $(basename ${KERNEL_XZ_PATH})
    cd ${KERNEL_DIR}
    ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make defconfig
    ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make kvm_guest.config
    ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make -j8
    cp arch/arm64/boot/Image ${KERNEL_PATH}
    cd ..
fi

# # Resize the image with qemu-img by +4G
# echo -e "[!] Resizing the image with qemu-img by +4G...\n"
# qemu-img resize ${IMAGE_FILE} +4G

# # Mount the image into loop use fdisk to resize the partition then resize2fs
# echo -e "[!] Mounting the image into loop use fdisk to resize the partition...\n"
# sudo losetup -fP ${IMAGE_FILE}

# # Calculate the new start sector for the second partition
# echo -e "[!] Calculating the new start sector for the second partition...\n"
# NEW_START_SECTOR=$(sudo fdisk -l /dev/loop0 | grep ${IMAGE_FILE}2 | awk '{print $2}')
# echo -e "[!] New start sector: ${NEW_START_SECTOR}\n"
# # Calculate the new end sector for the second partition
# NEW_END_SECTOR=$(sudo fdisk -l /dev/loop0 | grep ${IMAGE_FILE}2 | awk '{print $3}')
# echo -e "[!] New end sector: ${NEW_END_SECTOR}\n"

# sudo fdisk -l /dev/loop0
# # Delete second partition then make new partition with the same start sector and the new end sector
# sudo fdisk /dev/loop0
# d
# 2
# n
# p
# 2
# ${NEW_START_SECTOR}
# ${NEW_END_SECTOR}
# w
# echo -e "[!] Resizing the partition...\n"
# sudo e2fsck -f -y /dev/loop0p2
# sudo resize2fs /dev/loop0p2
# echo -e "[!] Unmounting the image...\n"

sudo losetup -D

# Calculate the offset for mounting the image
echo -e "[!] Calculating the offset for mounting the image...\n"
SECTOR_SIZE=512
START_SECTOR=$(fdisk -l ${IMAGE_FILE} | grep ${IMAGE_FILE}2 | awk '{print $2}')
OFFSET=$((START_SECTOR * SECTOR_SIZE))
# 8192 * 512 = 4194304
OFFSET=4194304
echo -e "[!] Offset: ${OFFSET}\n"

# Mount the image
echo -e "[!] Mounting the image...\n"
sudo mkdir -p ${MOUNT_DIR}
sudo mount -o loop,offset=${OFFSET} ${IMAGE_FILE} ${MOUNT_DIR}

# Enable ssh and set username and password
cd ${MOUNT_DIR}
sudo touch ssh
echo "${USERNAME}:${PASSWORD_HASH}" | sudo tee userconf.txt
cd ..

# Unmount the image
sudo umount ${MOUNT_DIR}
sudo rmdir ${MOUNT_DIR}

# Run qemu emulator in the background
qemu-system-aarch64 -machine virt -cpu cortex-a72 -smp 6 -m 4G \
    -kernel ${KERNEL_PATH} -append "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0" \
    -drive format=raw,file=${IMAGE_PATH},if=none,id=hd0,cache=writeback \
    -device virtio-blk,drive=hd0,bootindex=0 \
    -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
    -device virtio-net-pci,netdev=mynet \
    -monitor telnet:127.0.0.1:5555,server,nowait &

QEMU_PID=$!

# check_ssh() {
#     ssh -o BatchMode=yes -o ConnectTimeout=5 -p 2222 pi@localhost exit
# }

# echo -e "[!] Waiting for SSH to become available...\n"
# while ! check_ssh; do
#     echo -e "[!] SSH not available yet. Retrying in 5 seconds...\n"
#     sleep 5
# done

# echo -e "[!] SSH is available. Performing other tasks...\n"
# echo -e "[!] QEMU is running with PID ${QEMU_PID}. Performing other tasks...\n"

# Example task: wait for 30 seconds
sleep 120

# Terminate the QEMU process
echo -e "[!] Terminating QEMU with PID ${QEMU_PID}.\n"
kill ${QEMU_PID}

echo -e "[!] Done!\n"
