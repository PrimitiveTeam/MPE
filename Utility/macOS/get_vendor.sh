#!/bin/bash

# Set working directory to the directory of the script
SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

echo "Setting up directories..."
mkdir -p $SCRIPT_DIR/../../Vendor/OSX
mkdir -p $SCRIPT_DIR/../../Vendor/Universal

# CD into Vendor
# Can't find GLAD for macOS
cd $SCRIPT_DIR/../../Vendor
cd ./Universal
# echo "Generating GLAD for OpenGL version 4.6..."
# glad --quiet --api gl:compatibility=4.6 --out-path ./Glad c

# imgui
# If imgui already exists, cancel next step
if [ -d "imgui" ]; then
    echo "imgui already exists. Skipping..."
else
    echo "Cloning imgui..."
    git clone https://github.com/ocornut/imgui.git
    cd imgui
    git checkout docking
    cd ..
fi

# stb
# If stb already exists, cancel next step
if [ -d "stb" ]; then
    echo "stb already exists. Skipping..."
else
    echo "Cloning stb..."
    git clone https://github.com/nothings/stb.git
fi

cd ../OSX

# renderdoc
# If renderdoc already exists, cancel next step
if [ -d "renderdoc" ]; then
    echo "renderdoc already exists. Skipping..."
else
    echo "Cloning renderdoc..."
    git clone https://github.com/baldurk/renderdoc.git
fi

# opencv
# If opencv already exists, cancel next step
if [ -d "opencv" ]; then
    echo "opencv already exists. Skipping..."
else
    echo "Cloning opencv..."
    git clone https://github.com/opencv/opencv.git
fi

cd opencv
echo "Generating and building OpenCV with Visual Studio 2022 - RELEASE"
cmake -S . -B ./Build -G "Xcode" -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=./Install/Release
cmake --build ./Build --config Release --target INSTALL
echo "Generating and building OpenCV with Visual Studio 2022 - DEBUG"

# cmake --build ./Build --config Debug --target INSTALL
cd ..

echo "Setup complete."
