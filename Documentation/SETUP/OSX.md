# Working with source - OSX

## Tools

The following tools are required to prepare the environment, generate and build the source code.

1. [CMake](https://cmake.org/)
2. [Git](https://git-scm.com/)
3. C++ compiler ([Clang](https://clang.llvm.org/) - macOS should have this built-in/[GCC](https://gcc.gnu.org/))
4. While [CPM](https://github.com/Durengo/CPM) is in alpha [Rust](https://www.rust-lang.org/) + [Cargo](https://crates.io/) is necessary to build the project manager

## Preparing environment

1. Download the repo: `$git clone git@github.com:Durengo/MPE.git --recursive`
2. Checkout 'dev' branch
3. Initialize git submodules: `$git submodule init`
4. CD into the /CPM/cpm: `$cd <repo root>/CPM/cpm`
5. Build CPM: `$cargo build --release`
6. __Make sure to cd back into repo root__
7. Execute `$./CPM/cpm/target/release/cpm.exe init -f`
8. After this 'cpm.sh' will appear in the __repo root__, this will be the entrypoint to the buildsystem
9. Check if it's working by executing `$./cpm.sh -v` from the __repo root__
10. Continue to [brew](#brew) section.

### BREW

For macOS [brew](https://brew.sh/) is __required__.

Download and install the following libraries with brew:

1. [fmt](https://github.com/fmtlib/fmt)
2. [spdlog](https://github.com/gabime/spdlog)
3. [glfw3](https://github.com/glfw/glfw)
4. [glm](https://github.com/g-truc/glm)
5. [freetype](https://freetype.org/)
6. [openal-soft](https://github.com/kcat/openal-soft)

<!-- TODO: Need to make gtest a universal package and built locally -->

Continue to [Manual building](#manual-building) section.

### Manual building

Scripts are provided to automate this step.

The following dependencies need to be downloaded and setup:

1. imgui
2. stb
3. renderdoc
4. opencv

glad is also a requirement but I have included it directly in the repository as the configuration can be finicky.

Use the [Utility/macOS/get_vendor.sh](../../Utility/macOS/get_vendor.sh) batch.

Continue to [Building source](#building-source) section.

### Building source

1. Run the setup script to check packages and setup the environment: (errors will appear but ignore those) `$./cpm.sh setup -a`
2. Generate CMake project for macOS using clang or gcc: `$./cpm.sh build -dg "make/clang"` or `$./cpm.sh build -dg "make/gcc"`
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

1. Execute: [./Utility/macOS/setup_angle.sh](../../Utility/macOS/setup_angle.sh)
