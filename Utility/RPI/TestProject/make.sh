#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "$0") && pwd)

# Variables
PROCESSER="aarch64"
COMPILER="aarch64-linux"
SYSROOT="/opt/rpi-sysroot"

echo "Make sure to set C and CXX compiler to a cross-compilation toolchain (THAT IS NOT EXTRACTED FROM SYSROOT)"

echo "Generating CMake project..."

cmake \
    -S ${SCRIPT_DIR} \
    -B ${SCRIPT_DIR}/build \
    -G "Unix Makefiles" \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_VERSION=1 \
    -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
    -DCMAKE_C_COMPILER=/usr/bin/${COMPILER}-gnu-gcc \
    -DCMAKE_CXX_COMPILER=/usr/bin/${COMPILER}-gnu-g++ \
    -DCMAKE_SYSROOT=${SYSROOT} \
    -DCMAKE_FIND_ROOT_PATH=${SYSROOT} \
    -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER \
    -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
    -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
    -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY \

echo "Building project..."

cmake --build ${SCRIPT_DIR}/build