#!/bin/bash

echo "Make sure to start VcXsrv first!"

# Configure WSL to Use the X Server
export DISPLAY=192.168.0.101:0
# Set the directory containing the kernel and image files
SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

# Define paths to the kernel and image
Kernel=$SCRIPT_DIR/linux-6.6.20-image
Image=$SCRIPT_DIR/2024-07-04-raspios-bookworm-arm64.img

# Start QEMU with graphical display enabled
qemu-system-aarch64 \
    -machine virt \
    -cpu cortex-a72 \
    -smp 6 \
    -m 4G \
    -kernel $Kernel \
    -append "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0" \
    -drive format=raw,file=$Image,if=none,id=hd0,cache=writeback \
    -device virtio-blk,drive=hd0,bootindex=0 \
    -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
    -device virtio-net-pci,netdev=mynet \
    -display sdl \
    -device virtio-gpu-pci \
    -device usb-ehci \
    -device usb-kbd \
    -device usb-mouse \
    -serial stdio
