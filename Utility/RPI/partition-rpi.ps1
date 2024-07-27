# Get the path of the current script
$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Get the kernel from script/kernel-qemu-4.4.34-jessie
# $kernelImage = "$scriptPath\kernel-qemu-4.4.34-jessie"
# $kernelImage = "$scriptPath\kernel-qemu-5.4.51-buster"

# Gparted
$gpartedImage = "$scriptPath\gparted-live.iso"

# Get the rapberry pi image from script/rpi.img
$raspbianImage = "$scriptPath\rpi.img"

# Ensure that the files exist
if (-Not (Test-Path $gpartedImage)) {
    Write-Error "GParted image not found at $gpartedImage"
    exit
}

if (-Not (Test-Path $raspbianImage)) {
    Write-Error "Raspberry Pi image not found at $raspbianImage"
    exit
}

# Run QEMU with the GParted Live CD and Raspberry Pi image
Start-Process -FilePath "qemu-system-arm" -ArgumentList @(
    "-M", "versatilepb",
    "-cpu", "arm1176",
    "-m", "256",
    "-drive", "file=$raspbianImage,if=none,index=0,media=disk,format=raw,id=disk0",
    "-device", "virtio-blk-pci,drive=disk0,disable-modern=on,disable-legacy=off",
    "-cdrom", "$gpartedImage",
    "-boot", "d",
    "-net", "nic",
    "-net", "user",
    "-serial", "stdio",
    "-display", "sdl",
    "-d", "int,cpu_reset,guest_errors"
)