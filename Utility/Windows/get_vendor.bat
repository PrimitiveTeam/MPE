@echo off
REM Set working directory to the directory of the script
SET SCRIPT_DIR=%~dp0

echo Setting up directories...
mkdir %SCRIPT_DIR%..\..\Vendor

REM CD into Vendor
cd %SCRIPT_DIR%..\..\Vendor

@REM Create WIN32 dir and cd into it
mkdir WIN32
mkdir Universal
cd Universal
@REM cd WIN32

echo Generating GLAD for OpenGL version 4.6...
glad --quiet --api gl:compatibility=4.6 --out-path .\Glad c
@REM glad --quiet --api gles2=3.0 --out-path .\Glad c

REM imgui
REM If imgui already exists, cancel next step
if exist "imgui" (
    echo imgui already exists. Skipping...
) else (
    echo Cloning imgui...
    git clone https://github.com/ocornut/imgui.git
    cd imgui
    git checkout docking
    cd ..
)

REM stb
REM If stb already exists, cancel next step
if exist "stb" (
    echo stb already exists. Skipping...
) else (
    echo Cloning stb...
    git clone https://github.com/nothings/stb.git
)

cd ../WIN32

REM renderdoc
REM If renderdoc already exists, cancel next step
if exist "renderdoc" (
    echo renderdoc already exists. Skipping...
) else (
    echo Cloning renderdoc...
    git clone https://github.com/baldurk/renderdoc.git
)


REM opencv
REM If opencv already exists, cancel next step
if exist "opencv" (
    echo opencv already exists. Skipping...
) else (
    echo Cloning opencv...
    git clone https://github.com/opencv/opencv.git
)

cd opencv
echo Generating and building OpenCV with Visual Studio 2022 - RELEASE
cmake -S . -B ./Build -G "Visual Studio 17 2022" -A x64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=./Install/Release
cmake --build ./Build --config Release --target INSTALL
echo Generating and building OpenCV with Visual Studio 2022 - DEBUG
cmake -S . -B ./Build -G "Visual Studio 17 2022" -A x64 -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=./Install/Debug
cmake --build ./Build --config Debug --target INSTALL
cd ..

echo Setup complete.
