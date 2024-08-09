#!/bin/bash

# Set working directory to the directory of the script
SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

echo "Setting up directories..."
mkdir -p $SCRIPT_DIR/../../Vendor/OSX
mkdir -p $SCRIPT_DIR/../../Vendor/Universal

# CD into Vendor
cd $SCRIPT_DIR/../../Vendor
cd ./OSX

# test if build_tools are installed
echo "MAKE SURE BUILD TOOLS ARE INSTALLED AND SET THE DIRECTORY IN THE PATH"

# test if build tools exist by running cipd --version
if ! command -v cipd &>/dev/null; then
    echo "cipd could not be found"
    echo "Please install depot_tools from https://dev.chromium.org/developers/how-tos/install-depot-tools"
    exit
fi

# angle
if [ -d "angle" ]; then
    echo "angle already exists. Skipping to build..."
else
    echo "Cloning angle..."
    git clone https://github.com/google/angle.git
fi

cd angle

echo "Bootstrapping angle..."
echo "If there are SSL errors, try:"
echo "$ open "/Applications/Python 3.12/Install Certificates.command""
# echo "If getting 'SyntaxError: Missing parentheses in call to 'print'. Did you mean print(...)?' fix the code in bootstrap.py"

echo "Installing ninja..."
brew install ninja

# SSL certificates might be broken
# export PYTHONHTTPSVERIFY=0
# alias python=python3

python3 scripts/bootstrap.py
gclient sync
git checkout master

echo "Generating ANGLE..."
# We need to enable metal otherwise glfw throws this error:
# GLFW ERROR (65542): NSGL: OpenGL ES is not available via NSGL
# This is because ANGLE is not built with Metal support
gn gen out/Release \
    --args='
    is_component_build=false
    target_os="mac"
    target_cpu="x64"
    is_debug=false
    angle_assert_always_on=true
    angle_enable_d3d9=false
    angle_enable_d3d11=false
    angle_enable_gl=true
    angle_enable_metal=true
    angle_enable_null=false
    angle_enable_vulkan=false
    angle_enable_essl=true
    angle_enable_glsl=true
    '

echo "Building ANGLE..."
autoninja -C out/Release

cd ..

echo "Setup complete."
