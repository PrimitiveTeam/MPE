#!/bin/bash

# Set working directory to the directory of the script
SCRIPT_DIR=$(dirname "$(realpath "$0")")

echo "Setting up directories..."
mkdir -p "$SCRIPT_DIR/../../Vendor/RPI4"

# Change directory into Vendor
cd "$SCRIPT_DIR/../../Vendor/RPI4" || exit

# Check if "angle" directory already exists
if [ -d "angle" ]; then
    echo "angle already exists. Skipping..."
else
    echo "Cloning angle..."
    git clone https://chromium.googlesource.com/angle/angle
fi

cd angle

echo "Make sure depot_tools is downloaded and is in PATH"

echo "Bootstrapping angle..."
python scripts/bootstrap.py
gclient sync

echo "Getting dependencies..."
./build/install-build-deps.sh

echo "Generating Build Files for Release and Debug"
mkdir -p out/Release

gn gen out/Release \
    --args='
    is_component_build=false
    target_cpu="x64"
    is_debug=false
    angle_assert_always_on=true
    angle_enable_d3d9=false
    angle_enable_d3d11=false
    angle_enable_gl=true
    angle_enable_metal=false
    angle_enable_null=false
    angle_enable_vulkan=false
    angle_enable_essl=true
    angle_enable_glsl=true
    '

echo "Building angle"
autoninja -C out/Release