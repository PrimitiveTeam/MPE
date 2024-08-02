#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

Kernel=$SCRIPT_DIR/linux-6.6.20-image
Image=$SCRIPT_DIR/2024-07-04-raspios-bookworm-arm64.img

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
    -monitor telnet:127.0.0.1:5555,server,nowait \
    -nographic
