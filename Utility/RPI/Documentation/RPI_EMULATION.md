# Emulating Raspberry Pi 4 with Qemu

> **Just a quick update before we dive in:** what we're actually doing here is running Raspberry Pi OS (64-bit) on a QEMU virtual ARM setup. This isn't full-blown hardware emulation of the Raspberry Pi 4, but more about creating a virtual environment for the OS. It doesn't mimic all the specific hardware features of the Pi 4, but it's pretty useful and great for general testing. I turned to this solution mainly to extract a modified sysroot from the Raspberry Pi OS, something not readily available in other resources. For those looking into detailed emulation of the actual Raspberry Pi 4's hardware in QEMU, check out this link for the latest updates: https://gitlab.com/qemu-project/qemu/-/issues/1208.

Hope it helps! :D

Shortcomings: No GUI yet, only console.

# Steps

1. Download **Raspberry Pi OS (64-bit)** from [Raspberry Pi operating system images](https://www.raspberrypi.com/software/operating-systems/#raspberry-pi-os-64-bit). <br>Here we downloaded Raspberry Pi OS (64-bit) with desktop, Kernel version: 6.1, Debian version: 11 (bullseye), Release date: May 3rd 2023, named `2023-05-03-raspios-bullseye-arm64.img`. We put it in `/home/mydir`.
3. Install the required packages on your host system:
    ```shell
    $ # Cross compilers for arm64
    $ sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
    
    $ # Qemu itself
    $ sudo apt install qemu qemubuilder qemu-system-gui qemu-system-arm qemu-utils \
        qemu-system-data qemu-system
    ```
4. Build the Linux kernel for qemu arm64 (You can download the kernel from [Kernel.org](https://www.kernel.org/)):
    ```shell
    $ wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.34.tar.xz
    $ tar xvJf linux-6.1.34.tar.xz
    $ cd linux-6.1.34
    
    $ # create a .config file
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make defconfig
    $ # Use the kvm_guest config as the base defconfig, which is suitable for qemu
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make kvm_guest.config
    $ # Build the kernel
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make -j8

    $ cp arch/arm64/boot/Image /home/mydir
    ```
3. Mount the image for enabling ssh and configuring username and password:
    1. Get the correct offset value with the help of `fdisk` utility:
        ```shell
        $ fdisk -l 2023-05-03-raspios-bullseye-arm64.img
        Disk 2023-05-03-raspios-bullseye-arm64.img: 4.11 GiB, 4412407808 bytes, 8617984 sectors
        Units: sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disklabel type: dos
        Disk identifier: 0x3e247b30
        Device                                 Boot  Start     End Sectors  Size Id Type
        2023-05-03-raspios-bullseye-arm64.img1        8192  532479  524288  256M  c W95 FAT32 (LBA)
        2023-05-03-raspios-bullseye-arm64.img2      532480 8617983 8085504  3.9G 83 Linux
        ```
        As we can see, we have two partitions inside the downloaded image. The first device (partition) is the bootable partition, and the second one is the root filesystem. The first partition is what will be mounted as `/boot` in Raspberry Pi, and this is where we'll need to create some files.
        <br>Obtain the correct **offset** of the first device by multiplying the start of the first partition (here 8192) by the sector size (here 512).
Here it will be calculated as **8192 * 512 = 4194304**
    2. Mount the image in `/mnt/rpi` directory:
        ```shell
        $ sudo mkdir /mnt/rpi
        $ sudo mount -o loop,offset=4194304 2023-05-03-raspios-bullseye-arm64.img /mnt/rpi
        ```
    3. Create a file named `ssh` to enable ssh:
        ```shell
        $ cd /mnt/rpi
        $ sudo touch ssh
        ```
    4. Additionally, create a file named `userconf.txt` in the same directory and put your desired username and password there, like `<username>:<hashed-password>` (might be better to leave the username as `pi`). This will be your default credentials:
        ```shell
        $ openssl passwd -6                                     # Generate the <hashed-password>
        $ echo 'pi:<hashed-password>' | sudo tee userconf.txt   # Put them inside `userconf.txt`
        ```
    5. Finally, unmount the image:
        ```shell
        $ sudo umount /mnt/rpi
        ```
4. Run qemu emulator:
    ```shell
    $ cd /home/mydir
    $ qemu-system-aarch64 -machine virt -cpu cortex-a72 -smp 6 -m 4G \
        -kernel Image -append "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0" \
        -drive format=raw,file=2023-05-03-raspios-bullseye-arm64.img,if=none,id=hd0,cache=writeback \
        -device virtio-blk,drive=hd0,bootindex=0 \
        -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
        -device virtio-net-pci,netdev=mynet \
        -monitor telnet:127.0.0.1:5555,server,nowait
    ```
    This machine will be able to access the internet.
5. After the machine is completely booted up, you can login to it from your computer by using ssh and the username and password you specified:
    ```shell
    $ ssh -l pi localhost -p 2222
    ```
6. Done!

# Troubleshooting

* If you had any problem with connecting to internet, it might be because of bad DNS configurations, and you should consider adding `nameserver 8.8.8.8` to top of the file `/etc/resolv.conf` in the machine. 
* You can access the qemu monitor console with:
    ```shell
    $ telnet localhost 5555
    ```