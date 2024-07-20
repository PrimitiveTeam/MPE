#!/bin/bash

# Set working directory to the directory of the script
SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

echo "Setting up directories..."
mkdir -p $SCRIPT_DIR/../../Vendor

# CD into Vendor
cd $SCRIPT_DIR/../../Vendor
echo "Generating GLAD for OpenGL version 4.6..."
glad --quiet --api gl:compatibility=4.6 --out-path ./Glad c

# imgui
# If imgui already exists, cancel next step
if [ -d "imgui" ]; then
    echo "imgui already exists. Skipping..."
else
    echo "Cloning imgui..."
    git clone https://github.com/ocornut/imgui.git
    cd imgui
    git checkout docking
fi

# stb
# If stb already exists, cancel next step
if [ -d "stb" ]; then
    echo "stb already exists. Skipping..."
else
    echo "Cloning stb..."
    git clone https://github.com/nothings/stb.git
fi

# renderdoc
# If renderdoc already exists, cancel next step
if [ -d "renderdoc" ]; then
    echo "renderdoc already exists. Skipping..."
else
    echo "Cloning renderdoc..."
    git clone https://github.com/baldurk/renderdoc.git
fi

echo "Setup complete."
