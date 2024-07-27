# Get the path of the current script
$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Definition


# Get the kernel from script/kernel-qemu-4.4.34-jessie
# $kernelImage = "$scriptPath\kernel-qemu-4.4.34-jessie"
$kernelImage = "$scriptPath\kernel-qemu-5.4.51-buster"

# DTB
$dtb = "$scriptPath\versatile-pb-buster-5.4.51.dtb"

# Get the rapberry pi image from script/rpi.img
$raspbianImage = "$scriptPath\rpi.img"

# Start the QEMU emulator with the specified parameters
# qemu-system-arm `
#   -M versatilepb `
#   -cpu arm1176 `
#   -m 256 `
#   -hda $raspbianImage `
#   -net user,hostfwd=tcp::5022-:22 `
#   -kernel $kernelImage `
#   -append "root=/dev/sda2 panic=1" `
#   -no-reboot #`
#   # -serial stdio `
#   # -net nic

# qemu-system-arm `
#   -M versatilepb `
#   -cpu arm1176 `
#   -m 256 `
#   -drive "file=$raspbianImage,if=none,index=0,media=disk,format=raw,id=disk0" `
#   -device "virtio-blk-pci,drive=disk0,disable-modern=on,disable-legacy=off" `
#   -netdev user,id=mynet0,hostfwd=tcp::5022-:22 `
#   -device rtl8139,netdev=mynet0 `
#   -dtb $dtb `
#   -kernel $kernelImage `
#   -append 'root=/dev/vda2 panic=1' `
#   -no-reboot `
#   -serial stdio

# qemu-system-arm `
#   -M versatilepb `
#   -cpu arm1176 `
#   -m 256 `
#   -drive "file=$raspbianImage,if=none,index=0,media=disk,format=raw,id=disk0" `
#   -device "virtio-blk-pci,drive=disk0,disable-modern=on,disable-legacy=off" `
#   -net nic `
#   -net user,hostfwd=tcp::5022-:22,hostfwd=tcp::8080-:80 `
#   -dtb $dtb `
#   -kernel $kernelImage `
#   -append 'root=/dev/vda2 panic=1' `
#   -no-reboot `
#   -serial stdio



  # -net user,hostfwd=tcp::5022-:22 `




# WILL MOST LIKELY NEED TO SETUP TAP DEVICE
# https://community.openvpn.net/openvpn/wiki/ManagingWindowsTAPDrivers#Introduction

# ❯ openvpn --show-adapters
# Available adapters [name, GUID, driver]:
# 'OpenVPN TAP-Windows6' {88D51518-E936-4520-89C8-4FE5EC7E4250} tap-windows6
#    Sebas@SWPC  D:  WORK  GIT  MPE  dev 
# ❯ tapctl.exe
# OpenVPN 2.6.12

# Usage:

# tapctl <command> [<command specific options>]

# Commands:

# create     Create a new TUN/TAP adapter
# list       List TUN/TAP adapters
# delete     Delete specified network adapter
# help       Display this text

# Hint: Use "tapctl help <command>" to display help for particular command.
#    Sebas@SWPC  D:  WORK  GIT  MPE  dev   
# ❯ tapctl create --name qemurasp
# {7D31B41C-C948-40C3-91DD-F3DDCA32B545}
#    Sebas@SWPC  D:  WORK  GIT  MPE  dev 
# ❯ netsh interface ip set address name="qemurasp" static 192.168.50.1 255.255.255.0

#    Sebas@SWPC  D:  WORK  GIT  MPE  dev 
# ❯ openvpn --show-adapters
# Available adapters [name, GUID, driver]:
# 'OpenVPN TAP-Windows6' {88D51518-E936-4520-89C8-4FE5EC7E4250} tap-windows6
# 'OpenVPN TAP-Windows6 #1' {CC40BD00-EC6F-4C5B-B415-FDD44FCBBD18} tap-windows6
# 'qemurasp' {7D31B41C-C948-40C3-91DD-F3DDCA32B545} tap-windows6

# THEN ON GUEST OS

# sudo ifconfig eth0 up
# sudo ifconfig eth0 192.168.50.2 netmask 255.255.255.0

# make sure to enable ssh on raspbian


# HOST MACHINE

# scp -r ./cross-pi-gcc/ pi@192.168.50.2:/home/pi

# rsync -avz --rsync-path="sudo rsync" pi@192.168.50.2:/ /home/seb/raspberrypi/rootfs/


qemu-system-arm `
  -M versatilepb `
  -cpu arm1176 `
  -m 256 `
  -drive "file=$raspbianImage,if=none,index=0,media=disk,format=raw,id=disk0" `
  -device "virtio-blk-pci,drive=disk0,disable-modern=on,disable-legacy=off" `
  -net nic `
  -net tap,ifname=qemurasp,script=no,downscript=no `
  -dtb $dtb `
  -kernel $kernelImage `
  -append "root=/dev/vda2 panic=1 console=ttyAMA0" `
  -no-reboot `
  -serial stdio
