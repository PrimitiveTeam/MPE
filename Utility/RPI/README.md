# BUILDING MPE TO RASPBERRY PI

Currently supported version of raspiOS: Debian 12 (bookworm) GNU/Linux / Linux Kernel 6.6.20 / aarch64-gnu

## Links

* [raspios_arm64-2024-07-04](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2024-07-04/)
* [raspios info](https://downloads.raspberrypi.org/raspios_full_arm64/archive/2024-07-04-17:25/)
* [linux-6.6.20](https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.20.tar.xz)
* [One Drive Link](https://1drv.ms/f/s!AmBWkGOxnjxShNgHV7VWMnsPDGmxTw?e=717CVr)

## Requirements for Windows

1. [WSL-Ubuntu](https://learn.microsoft.com/en-us/windows/wsl/install)
2. The following packages for WSL-Ubuntu:
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
    * one-liner command:
    * sudo apt-get install qemu qemubuilder qemu-system-gui qemu-system-arm qemu-system-data qemu-system qemu-utils qemu-efi openssl openssh-server g++ gcc tar build-essential cmake unzip git python pkg-config rsync wget gcc-aarch64-linux-gnu g++-aarch64-linux-gnu

## Requirements for macOS

WIP

## Build, Compile, and Emulate

If you have physical hardware, great! You're life is 1000x easier. If not, then some headaches are bound your way.

Above is a link to OneDrive which has everything you need: kernel, prepared RPI image, packaged sysroot. So use that unless you want to destroy your brain.

First things first, we need to compile a linux kernel. Either use an existing kernel/image combination or do it yourself.
The following guide made by @cGandom shows how to compile the kernel, edit the image, and launch the qemu emulator: [RPI_EMULATION](./Documentation/RPI_EMULATION.md)
Running the ['setup_rpi.sh'](./setup_rpi.sh) script in WSL will do all of this for you.

NOTE: When building the kernel there are specific commands to make rendering work check [the next section](#building-kernel-to-enable-rendering)

## Dependencies and Sysroot

To successfully cross-compile a project we need respective compilers but we also need the sysroot of the system to acquire all the libraries (like cpp standard library).
Sysroot is essentially '/' copy of the whole system.

### Building with Windows-WSL

This could also work with UNIX systems (probably...)

TODO: Investigate the package section as it looks like the RPI system might not actually need any packages and we instead we can provide local source and the compiler should build it for our target.

1. Start RPI environment (./start_headless)
2. `$ sudo apt-get install -y git cmake pkg-config libfmt9 libspdlog1.10 libglfw3 xorg-dev libglm-dev libgtest-dev libgtk-3-dev`
3. GLFW:
    * `$ cd $home`
    * `$ git clone https://github.com/glfw/glfw`
    * `$ cd glfw`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
4. fmt:
    * `$ cd $home`
    * `$ git clone https://github.com/fmtlib/fmt.git`
    * `$ cd fmt`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
5. spdlog:
    * `$ cd $home`
    * `$ git clone https://github.com/gabime/spdlog.git`
    * `$ cd fmt`
    * `$ cmake -DBUILD_SHARED_LIBS=ON .`
    * `$ make`
    * `$ sudo make install`
6. Start an instance of WSL
7. While RPI is running and a WSL environment is available:
   `$ ssh -p 2222 pi@localhost "sudo tar --numeric-owner -czf - --exclude=/dev/* --exclude=/proc/* --exclude=/sys/* --exclude=/tmp/* --exclude=/run/* --exclude=/mnt/* --exclude=/media/* --exclude=/lost+found /" > /tmp/rpi-sysroot.tar`
8. Extract tar to /opt/rpi-sysroot: `$ sudo mkdir /opt/rpi-sysroot && sudo tar -xf rpi-sysroot.tar -C /opt/rpi-sysroot`
9. In WSL system cd into [TestProject](./TestProject/)
10. `$ ./make.sh`

If the build is successful then you are ready for cross-compilation!

### Cross-Compiling MPE

If running Windows-WSL make sure to run these commands from WSL

1. `$ cd /CPM/cpm`
2. `$ cargo build --release`
3. `$ cd ../..`
4. `$ ./CPM/cpm/target/release/cpm init -f`
5. `$ ./cpm.sh setup -a`
6. `$ ./cpm.sh cross-build -c -dg "rpi4/umake" --processor "aarch64" --sysroot "/opt/rpi-sysroot" -b`
7. Using SCP copy the contents of /build into the RPI machine
8. Run executable

### Windows Native QEMU or WSL-Ubuntu QEMU Display

1. First we need an x-server on our Windows machine: [VcXsrv](https://sourceforge.net/projects/vcxsrv/)
2. Start the [config.launch](./config.xlaunch)
3. In the RPI environment: `$ sudo apt-get install -y x11-apps`
4. Use start_gui script

### Building kernel to enable rendering

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

#### Hardware Acceleration

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



<!-- TODO GLFW
https://forums.raspberrypi.com/viewtopic.php?t=222264



I've got glfw running on a Raspberry Pi 4 with 4.19 Raspbian, including the triangle-opengl example. To save everybody a ton of time here is how I did it.

Forget messing around with 64-bit versions of Linux. Just install the latest 32-bit version of Raspbian which will have all the nice OpenGL hardware acceleration enabled by default.

Install Dependencies

sudo apt install git
sudo apt install xorg-dev

Download and install GLFW as follows (as user pi):

cd $home
git clone https://github.com/glfw/glfw
cd glfw
cmake -DBUILD_SHARED_LIBS=ON .
make
sudo make install

The download includes some nice examples, including triangle-opengl but that won't run yet as it targets the wrong version of OpenGL. The Raspberry Pi 4 supports up to OpenGL ES 3.1 so make the following changes to examples/triangle-opengl.c

Around line 89 replace the glfwWindowHint lines with the following ones:

glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

Around line 51 replace the #version line (vertex shader) with the following line:

"#version 310 es\n"

Around line 63 replace the #version line (fragment shader) with the following 2 lines:

"#version 310 es\n"
"precision mediump float;\n"

Now build and run the triangle-opengl example as follows:

make triangle-opengl
./examples/triangle-opengl

If all is well you should see a window with a spinning colourful triangle in it.

Good luck!

 -->