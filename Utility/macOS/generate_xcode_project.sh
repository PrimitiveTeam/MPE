#!/bin/bash

# Set working directory to the directory of the script
SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

echo "Setting up directories..."
mkdir -p $SCRIPT_DIR/../../ProjectFiles/Xcode

echo "Generating Xcode project..."
cmake -S $SCRIPT_DIR/../../ -B $SCRIPT_DIR/../../ProjectFiles/Xcode -G Xcode

echo "Setup complete."
