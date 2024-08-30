# Working with source - Raspberry Pi 4

## Cross-Compilation Support Matrix

|   Platform    | Native  | Cross-Compilation |
| :-----------: | :-----: | :---------------: |
|    Windows    | __NO__  |      __NO__       |
| Windows (WSL) | __NO__  |      __YES__      |
|     UNIX      | __NO__  |      __YES__      |
|     macOS     | __NO__  |      __YES__      |
|     RPI4      | __YES__ |      __NO__       |

Currently only Windows - WSL has been documented to work for cross-compilation. Other systems need to be investigated.

Currently supported version of raspiOS: Debian 12 (bookworm) GNU/Linux / Linux Kernel 6.6.20 / aarch64-gnu

Older versions will most likely work as well but that is not currently supported.

## Links

* [raspios_arm64-2024-07-04](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2024-07-04/)
* [raspios info](https://downloads.raspberrypi.org/raspios_full_arm64/archive/2024-07-04-17:25/)
* [linux-6.6.20](https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.20.tar.xz)

If you want to use an older toolchain you can acquire one here [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain)

[OneDrive Link](https://1drv.ms/f/s!AmBWkGOxnjxShNgHV7VWMnsPDGmxTw?e=717CVr) - here you will find a prepared image and kernel, so no need to build anything.

If using the OneDrive link to download the kernel, image, and sysroot make sure to extract kernel and image to `/Utility/RPI` and sysroot to `/opt`.

## Tools

1. [QEMU](https://www.qemu.org/) - On Windows make sure to get x64 binaries

Move to [Cross-Compilation Requirements](#cross-compilation-requirements) section

## Cross-Compilation Requirements

* [For Windows-WSL-Ubuntu or Ubuntu](#windows-wslubuntu)
* [For OSX](#osx)

### Windows-WSL/Ubuntu

Make sure that [WSL-Ubuntu](https://learn.microsoft.com/en-us/windows/wsl/install) is enabled and is installed.

Follow the [UNIX](./UNIX.md) working with source guide and set up your WSL environment.

The following packages are required for WSL-Ubuntu:

One-liner command:

```Bash
$sudo apt-get install qemu qemubuilder qemu-system-gui qemu-system-arm qemu-system-data qemu-system qemu-utils qemu-efi openssl openssh-server g++ gcc tar build-essential cmake unzip git python pkg-config rsync wget gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

1. qemu (FULL INSTALL)
2. qemubuilder
3. qemu-system-gui
4. qemu-system-arm
5. qemu-system-data
6. qemu-system
7. qemu-utils
8. qemu-efi
9. openssl
10. openssh-server
11. gcc-aarch64-linux-gnu
12. g++-aarch64-linux-gnu
13. g++
14. gcc
15. tar
16. build-essential
17. cmake
18. unzip
19. git
20. python
21. pkg-config
22. rsync
23. wget

Move to [Building Kernel](#building-kernel) section

### OSX

#### Cross-Compiling on Intel mac

__WORK IN PROGRESS__ Get the cross-compiler.

```bash
$brew tap messense/macos-cross-toolchains
# install aarch64-unknown-linux-gnu toolchain
$brew install aarch64-unknown-linux-gnu
$brew install aarch64-elf-gcc
```

Different compilers are available on mac, more info [here](https://github.com/messense/homebrew-macos-cross-toolchains).

## Building Kernel

If you have physical hardware, great! You're life is 1000x easier. If not, then some headaches are bound your way. To cross-compile MPE we need a linux system that has the appropriate compiler as well as the system root of the target machine, in this case raspberry pi 4. If you have a machine then you can skip this section.

You can also skip this step if you have downloaded the kernel from the [OneDrive link](#links) -> move to the [Setting Up And Extracting System Root](#setting-up-and-extracting-system-root) section.

This is another reminder that above is a link to OneDrive which has everything you need: kernel, prepared RPI image, packaged sysroot. So use that unless you want to destroy your brain.

The following guide made by @cGandom shows how to compile the kernel, edit the image, and launch the qemu emulator: [RPI_EMULATION](./Documentation/RPI_EMULATION.md)
Running the ['setup_rpi.sh'](./../../Utility/RPI/setup_rpi.sh) script in WSL will do all of this for you. Please note that the script is still under development and may not cover all edge cases.

__IF YOU NEED TO EMULATE RENDERING:__ When building the kernel there are specific commands to make rendering work check [the next section](#building-kernel-to-enable-rendering)

After building the kernel move to the [Setting Up And Extracting System Root](#setting-up-and-extracting-system-root) section.

### Building kernel to enable rendering

The include kernel already has rendering enabled.

Launch WSL and cd into linux-*.*.**

`$ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make defconfig`

`$ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make kvm_guest.config`

The previous command does this:

```plain-text
Value of CONFIG_SCSI_VIRTIO is redefined by fragment ./kernel/configs/kvm_guest.config:
Previous value: # CONFIG_SCSI_VIRTIO is not set
New value: CONFIG_SCSI_VIRTIO=y

Value of CONFIG_VIRTIO_INPUT is redefined by fragment ./kernel/configs/kvm_guest.config:
Previous value: # CONFIG_VIRTIO_INPUT is not set
New value: CONFIG_VIRTIO_INPUT=y

Value of CONFIG_DRM_VIRTIO_GPU is redefined by fragment ./kernel/configs/kvm_guest.config:
Previous value: # CONFIG_DRM_VIRTIO_GPU is not set
New value: CONFIG_DRM_VIRTIO_GPU=y
```

Now we need to make sure that the proper modules are installed so we can display through qemu.

`$ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make menuconfig`

* Device Drivers -> Graphics Support -> Virtual Display (set to '*')
* Device Drivers -> Virtualization drivers (set to '*')

Following might be optional:

* Device Drivers -> Graphics Support -> DRM driver for VMware Virtual GPU (set to 'M')

**MAKE SURE TO SAVE (OVERRIDE)**!

Now compile the kernel (MIGHT TAKE A WHILE):

`$ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make -j8 Image`

`$ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make -j8 Modules`

`$ mkdir -p /tmp/rpi-modules`

`$INSTALL_MOD_PATH=/tmp/rpi-modules ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make modules_install`

Start RPI environment (./start_gui.sh)

**On guest machine**:

`$ sudo mkdir -p /lib/modules/6.6.20`

`$ sudo scp -r <user>@<wsl_ip>:/tmp/rpi-modules/6.6.20/ /lib/modules/6.6.20`

`$ sudo modprobe virtio_gpu`
`$ lsmod | grep virtio`

Reboot guest

Make sure it's running and no errors are displayed:

`$ lsmod | grep virtio`

`$ dmesg | grep -i 'virtio'`

__NOTE__ this does not include hardware acceleration meaning that performance will be terrible. There is a WIP guide on how to make it work [Hardware Acceleration](#hardware-acceleration) section.

## Setting Up And Extracting System Root

To successfully cross-compile a project we need respective compilers but we also need the sysroot of the system to acquire all the libraries (like cpp standard library).
Sysroot is essentially '/' copy of the whole system.

First things first, download an RPI image, or use the one provided in [OneDrive link](#links).
There is also a tar containing a prepared sysroot for the same image [OneDrive link](#links).

If emulating RPI with qemu move to [Emulating RPI](#emulating-rpi) section.

### Emulating RPI

RPI can be emulated both natively (Windows and UNIX) and through WSL.

There are scripts ready to be run directly from a Windows machine or UNIX machine (WSL included).

If running on Windows make sure to install QEMU x64 and add it to your path.

Scripts, images, and kernels must be located in the /Utility/RPI/ folder.
Once you have the kernel compiled and image run the .\start_headless.ps1 for Windows machines or ./start_headless.sh for UNIX machines.

If using provided kernels and images the username is `pi` and the password is `pi`.

Move to the [Setting up the RPI system](#setting-up-the-rpi-system).

### Setting up the RPI system

If you have downloaded the image from [OneDrive link](#links) this is already done and you can move on to the [Building Source]() section.

These steps are intended for the RPI - emulated or hardware.

TODO: Investigate the package section as it looks like the RPI system might not actually need any packages and we instead we can provide local source and the compiler should build it for our target.

1. Start RPI environment (./start_headless)
2. Get packages: `$ sudo apt-get install -y git cmake pkg-config libfmt9 libspdlog1.10 libglfw3 xorg-dev libglm-dev libgtest-dev libgtk-3-dev libopenal1 libopenal-dev libfreetype-dev libfreetype6 libfreetype6-dev`
3. Manually download and build GLFW:
    * `$ cd $home`
    * `$ git clone https://github.com/glfw/glfw`
    * `$ cd glfw`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
4. Manually download and build fmt:
    * `$ cd $home`
    * `$ git clone https://github.com/fmtlib/fmt.git`
    * `$ cd fmt`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
5. Manually download and build spdlog:
    * `$ cd $home`
    * `$ git clone https://github.com/gabime/spdlog.git`
    * `$ cd fmt`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
6. (WINDOWS ONLY) Start an instance of WSL
7. While RPI is running (WINDOWS ONLY - and another WSL environment is available):
   `$ ssh -p 2222 pi@localhost "sudo tar --numeric-owner -czf - --exclude=/dev/* --exclude=/proc/* --exclude=/sys/* --exclude=/tmp/* --exclude=/run/* --exclude=/mnt/* --exclude=/media/* --exclude=/lost+found /" > /tmp/rpi-sysroot.tar`
8. Extract tar to /opt/rpi-sysroot: `$ sudo mkdir /opt/rpi-sysroot && sudo tar -xf rpi-sysroot.tar -C /opt/rpi-sysroot`
9. cd into [TestProject](./TestProject/)
10. `$ ./make.sh`

If the build is successful then you are ready for [cross-compilation](#cross-compiling-mpe)!

## Cross-Compiling MPE

We need to make sure that our source is setup. Please follow the [Working with source - UNIX](./UNIX.md) guide or use the shorthand here:

1. `$ cd /CPM/cpm`
2. `$ cargo build --release`
3. `$ cd ../..`
4. `$ ./CPM/cpm/target/release/cpm init -f`
5. `$ ./cpm.sh setup -a`
6. `$ ./cpm.sh cross-build -c -dg "rpi4/umake" --processor "aarch64" --sysroot "/opt/rpi-sysroot" -b`
7. Using SCP copy the contents of /build into the RPI machine like `$scp -P 2222 -r ./build pi@localhost:~/` to recursively copy the build folder
8. Run executable

If you are emulating RPI and need to display graphics or a window follow the [QEMU Display](#qemu-display) section.

## QEMU Display

## Windows Native QEMU or WSL-Ubuntu QEMU Display

1. First we need an x-server on our Windows machine: [VcXsrv](https://sourceforge.net/projects/vcxsrv/)
2. Start the [config.launch](./../../Utility/RPI/config.xlaunch)
3. In the RPI environment: `$ sudo apt-get install -y x11-apps`
4. Use start_gui script

## Hardware Acceleration

Currently I have not solved this but I'm keeping these instructions for reference.

create file `/etc/X11/xorg.conf.d/20-virtio-gpu.conf`:

```plain-text
Section "Device"
    Identifier "Virtio GPU"
    Driver "modesetting"
    Option "AccelMethod" "glamor"
EndSection
```
Check if hardware or software issue

(hardware check)
glxinfo | grep "OpenGL"

(software check)
LIBGL_ALWAYS_SOFTWARE=1 glxinfo | grep "OpenGL"

or also try
sudo nano `/etc/X11/xorg.conf.d/20-virtio-gpu.conf`:
```plain-text
Section "Module"
    Load "dri3"
EndSection

Section "Device"
    Identifier "Virtio GPU"
    Driver "modesetting"
    Option "AccelMethod" "glamor"
    Option "DRI" "3"
EndSection
```
sudo apt-get install xserver-xorg-video-modesetting libgl1-mesa-dri libgl1-mesa-glx libglx-mesa0 mesa-utils

lsmod | grep drm
lsmod | grep virtio_gpu

if not loaded load them manually
sudo modprobe drm
sudo modprobe virtio_gpu

check for errors
dmesg | grep -i 'drm'
dmesg | grep -i 'virtio'
