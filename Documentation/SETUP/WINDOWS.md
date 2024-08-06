# Working with source - Windows

## Tools

The following tools are required to prepare the environment, generate and build the source code.

1. [CMake](https://cmake.org/)
2. [Git](https://git-scm.com/)
3. C++ compiler ([MSVC](https://visualstudio.microsoft.com/downloads/)/[Clang](https://clang.llvm.org/)/[GCC](https://gcc.gnu.org/))
4. While [CPM](https://github.com/Durengo/CPM) is in alpha [Rust](https://www.rust-lang.org/) + [Cargo](https://crates.io/) is necessary to build the project manager

## Preparing environment

1. Download the repo: `$git clone git@github.com:Durengo/MPE.git --recursive`
2. Checkout 'dev' branch
3. Initialize git submodules: `$git submodule init`
4. CD into the /CPM/cpm: `$cd <repo root>\CPM\cpm`
5. Build CPM: `$cargo build --release`
6. __Make sure to cd back into repo root__
7. Execute `$.\CPM\cpm\target\release\cpm.exe init -f`
8. After this 'cpm.bat' will appear in the __repo root__, this will be the entrypoint to the buildsystem
9. Check if it's working by executing `$.\cpm -v` from the __repo root__
10. Continue to [VCPKG](#vcpkg) section.

### VCPKG

For windows [VCPKG](https://vcpkg.io/) is __required__.

After installing vcpkg make sure to add VCPKG to your path.

Download and install the following libraries with vcpkg (make sure to get the x64-windows triplet):

1. [fmt](https://github.com/fmtlib/fmt)
2. [spdlog](https://github.com/gabime/spdlog)
3. [glfw3](https://github.com/glfw/glfw)
4. [glm](https://github.com/g-truc/glm)
5. [gtest](https://github.com/google/googletest)

Continue to [Manual building](#manual-building) section.

### Manual building

Scripts are provided to automate this step.

The following dependencies need to be downloaded and setup:

1. imgui
2. stb
3. renderdoc
4. opencv

glad is also a requirement but I have included it directly in the repository as the configuration can be finicky.

Use the [Utility\Windows\get_vendor.bat](../../Utility/Windows/get_vendor.bat) batch.

Continue to [Building source](#building-source) section.

### Building source

1. Run the setup script to check packages and setup the environment: `$.\cpm setup -a`
2. Generate CMake project for windows using MSVC: `$.\cpm build -dg "nt/msvc"`
3. Build the generated CMake project: `$.\cpm build -db`

For more building instruction using CPM refer to the [how to use](./../../CPM/README.md#how-to-use) section.

## Toggle Graphics APIs

In the main [CMakeLists.txt](../../CMakeLists.txt) at the top-most of the file there are these definitions:

```CMake
set(MPE_OPENGL ON)
set(MPE_OPENGLES ON)
```

If both are enabled, then sources for both graphical APIs will be generated but OpenGL will be prioritized. If you want to use the OpenGLES API then disable MPE_OPENGL by setting it to 'OFF'.
If you're using the OpenGLES API refer to the [Building ANGLE](#building-angle) section.

## Building ANGLE

ANGLE is needed to use the OpenGLES API.

In [CMakeLists.txt](../../CMakeLists.txt) make sure the following is set:

```CMake
set(MPE_ANGLE ON)

set(MPE_OPENGL OFF)
set(MPE_OPENGLES ON)
```

### ANGLE Tools

The following tools are required to compile the ANGLE library:

1. Download [Python 3](https://www.python.org/downloads/)
2. Make sure to add Python3 to the path, test this by running: `$python3`
3. You will also need to make a symbolic link for python if ANGLE bootstrap is throwing errors: `$'mklink "C:\Dev\Tools\symlink\python3.exe" "C:\Program Files\Python312\python.exe"'`
4. Download [depot_tools](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up)
5. Make sure to add depot_tools to your path
6. Set DEPOT_TOOLS_WIN_TOOLCHAIN=0 in your environment (if you are not a Googler)
7. Make sure to have a Windows SDK installed like 10.0.22621.0, use Visual Studio Installer for this

Proceed to [Compiling ANGLE](#compiling-angle) section.

### Compiling ANGLE

1. Execute: [.\Utility\Windows\setup_angle.bat](../../Utility/Windows/setup_angle.ps1)
