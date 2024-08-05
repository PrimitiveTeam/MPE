# MPE

Small Game/Rendering Engine made from scratch in C++

## Documentation

Current documentation is minimal but available.

1. [MPE Core Engine](https://durengo.github.io/MPE/Documentation/MPE/html/index.html)

## Capabilities

### Platform

|     Windows     |      UNIX       |      macOS      | Raspberry PI 4 (RPI4) |
| :-------------: | :-------------: | :-------------: | :-------------------: |
|      __X__      |      __X__      |      __X__      |         __X__         |
| __64-bit only__ | __64-bit only__ | __64-bit only__ |   __32-bit/64-bit__   |

### Compiler

| Platform |  MSVC   |         GNU         |        CLANG        |
| :------: | :-----: | :-----------------: | :-----------------: |
| Windows  |  __X__  | Partially Supported | Partially Supported |
|   UNIX   | __N/A__ |        __X__        |        __X__        |
|  macOS   | __N/A__ |       __N/A__       |        __X__        |
|   RPI4   | __N/A__ |        __X__        |       __N/A__       |

## Working with Source and Requirements

### Supported IDE

1. VScode integration
2. (In Progress) Visual Studio

### Hardware

1. [OpenGL](https://www.opengl.org/) 4.6 compatible GPU

### For Compilation

1. [CMake](https://cmake.org/)
2. [Git](https://git-scm.com/)
3. C++ compiler ([MSVC](https://visualstudio.microsoft.com/downloads/)/[GCC](https://gcc.gnu.org/)/[Clang](https://clang.llvm.org/))
4. While [CPM](https://github.com/Durengo/CPM) is in alpha [Rust](https://www.rust-lang.org/) + [Cargo](https://crates.io/) is necessary to build the project manager

### Dependencies

For windows [VCPKG](https://vcpkg.io/) is __required__.

1. [fmt](https://github.com/fmtlib/fmt)
2. [spdlog](https://github.com/gabime/spdlog)
3. [glad](https://glad.dav1d.de/)
4. [glfw3](https://github.com/glfw/glfw)
5. [imgui](https://github.com/ocornut/imgui)
6. [glm](https://github.com/g-truc/glm)
7. [stb](https://github.com/nothings/stb)

### BUILDING

[QUICK SETUP](./Documentation/QUICK_SETUP.md)

1. Download the repo
2. Execute ``git submodule init``
3. CD into the __repo root__
4. CD into ``/CPM/cpm``
5. 1\~\*Execute ``cargo build --release``
6. CD into __the repo root__
7. Execute ``.\CPM\cpm\target\release\cpm.exe init -f``
8. After this 'cpm.bat' will appear in the __repo root__, this will be the entrrypoint to the buildsystem
9. Check if it's working by executing ``./cpm -V`` from the __repo root__
10. WINDOWS ONLY: Make sure to add VCPKG to your path
11. 2\~\*Execute ``./cpm setup -a`` to download packages and setup the environment
12. 3\~\*Execute ``./cpm build -dg <SYSTEM_TYPE>``
13. Execute ``./cpm build -db``
14. Run

1\~\* IT IS IMPORTANT TO BUILD IN RELEASE OTHERWISE THINGS MIGHT BREAK AS THE ALPHA VERSIONS DEBUG BUIDLS HAVE VERBOSE LOGGING.

2\~\* CPM MIGHT FAIL TO INSTALL ALL LIBRARIES DUE TO SOME ISSUE WITH ALPHA VERSION. IF THIS HAPPENS CHECK [cpm_install.json](cpm_install.json) AND INSTALL THE MISSING LIBRARIES.

3\~\* SINCE ONLY WINDOWS AND MSVC IS SUPPORTED THEN JUST RUN ``./cpm build -dg nt/msvc``

### BUILDING WITH OPENGLES

#### Dependencies For OpenGLES/Angle

Supported only on Windows

1. All of the above
2. [Python 3](https://www.python.org/downloads/) (also add to path)
3. You might also need to make a smybolic link of python3, e.g. 'mklink "C:\Dev\Tools\symlink\python3.exe" "C:\Program Files\Python312\python.exe"'
4. [depot_tools](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up) (also add to path)
5. Set DEPOT_TOOLS_WIN_TOOLCHAIN=0 in your environment if you are not a Googler
6. Windows SDK (10.0.22621.0)
7. Run .\Utility\Windows\setup_angle.bat

#### Building to RaspberryPi

For Windows:

1. Install [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain)
2. Add toolchain/bin to PATH
