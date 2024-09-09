# Working with source - UNIX

Currently the project has been tested on [Arch Linux](https://archlinux.org/) and Debian ([Ubuntu](https://ubuntu.com/)) - other distributions might not be supported.

## Tools

The following tools are required to prepare the environment, generate and build the source code.

1. [CMake](https://cmake.org/)
2. [Git](https://git-scm.com/)
3. C++ compiler ([Clang](https://clang.llvm.org/)/[GCC](https://gcc.gnu.org/))
4. While [CPM](https://github.com/Durengo/CPM) is in alpha [Rust](https://www.rust-lang.org/) + [Cargo](https://crates.io/) is necessary to build the project manager

## Preparing environment

1. Download the repo: `$git clone git@github.com:PrimitiveTeam/MPE.git --recursive`
2. CD into the repo root folder (ie. `$cd MPE`)
3. Checkout 'dev' branch
4. Initialize git submodules: `$git submodule init`
5. CD into /CPM/cpm: `$cd CPM/cpm`
6. Build CPM: `$cargo build --release`
7. __Make sure to cd back into repo root__
8. Execute `$./CPM/cpm/target/release/cpm init -f`
9. After this 'cpm.sh' will appear in the __repo root__, this will be the entrypoint to the buildsystem
10. Check if it's working by executing `$./cpm.sh -V` from the __repo root__
11. If everything is working, execute `./cpm.sh setup -a`  NOTE: This may throw errors about missing dependencies, which can be safely ignored for now.
12. Continue to [packages](#packages) section.

### Packages

Using the built-in package manager in UNIX systems the following libraries should be available.

Download and install the following libraries with a package manager:

Debian:

1. [libfmt-dev](https://github.com/fmtlib/fmt)
2. [libspdlog-dev](https://github.com/gabime/spdlog)
3. [libglfw3 and libglfw3-dev](https://github.com/glfw/glfw)
4. [libcglm-dev](https://github.com/g-truc/glm)
5. gtk3 is required - Ubuntu has it built-in
6. [freetype](https://freetype.org/)
7. [openal](https://github.com/kcat/openal-soft)

<!-- TODO: Need to make gtest a universal package and built locally -->

Arch:

1. [fmt](https://archlinux.org/packages/extra/x86_64/fmt/)
2. [spdlog](https://archlinux.org/packages/extra/x86_64/spdlog/)
3. [glfw](https://archlinux.org/packages/extra/x86_64/glfw/)
4. [glm](https://archlinux.org/packages/extra/x86_64/glm/)
5. [gtk3](https://archlinux.org/packages/extra/x86_64/gtk3/)
6. [gtest](https://archlinux.org/packages/extra/x86_64/gtest/)
7. [lib32-freetype2](https://archlinux.org/packages/multilib/x86_64/lib32-freetype2/)
8. [lib32-openal](https://archlinux.org/packages/multilib/x86_64/lib32-openal/)

Continue to [Manual building](#manual-building) section.

### Manual building

Scripts are provided to automate this step.

The following dependencies need to be downloaded and setup:

1. imgui
2. stb
3. renderdoc
4. opencv
5. entt

glad is also a requirement but I have included it directly in the repository as the configuration can be finicky.

Use the [Utility/Linux/get_vendor.sh](../../Utility/Linux/get_vendor.sh) batch.

Continue to [Building source](#building-source) section.

### Building source

1. Run the setup script to check packages and setup the environment: (errors will appear but ignore those) `$./cpm.sh setup -a`
2. Generate CMake project for Linux using clang or gcc: `$./cpm.sh build -dg "make/clang"` or `$./cpm.sh build -dg "make/gcc"`
3. Build the generated CMake project: `$./cpm.sh build -db`

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
3. Download [depot_tools](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up)
4. Make sure to add depot_tools to your path
5. Set DEPOT_TOOLS_WIN_TOOLCHAIN=0 in your environment (if you are not a Googler)

Proceed to [Compiling ANGLE](#compiling-angle) section.

### Compiling ANGLE

1. Execute: [./Utility/Linux/setup_angle.sh](../../Utility/Linux/setup_angle.sh)
