@echo off
REM Set working directory to the directory of the script
SET SCRIPT_DIR=%~dp0

echo Setting up directories...
mkdir %SCRIPT_DIR%..\..\Vendor

REM CD into Vendor
cd %SCRIPT_DIR%..\..\Vendor

REM angle
REM If angle already exists, cancel next step
if exist "angle" (
    echo angle already exists. Skipping...
) else (
    echo Cloning angle...
    git clone https://chromium.googlesource.com/angle/angle
    cd angle

    echo Bootstrapping angle...
    python scripts/bootstrap.py
    gclient sync

    echo Generating Build Files for Release and Debug
    mkdir out/Release
    cd out/Release
    gn gen .

    @REM mkdir out/Debug

    echo Building angle
    ninja -C .
)

echo Setup complete.

@REM gn gen out/Release --args="is_component_build=false is_debug=false angle_enable_vulkan=false angle_enable_d3d9=false angle_enable_d3d11=false angle_enable_gl=true angle_enable_metal=false angle_enable_swiftshader=false angle_enable_null=false" --ide=vs2022
@REM ninja -C out/Release

@REM gn gen out/Release --args="is_component_build=false is_debug=false angle_enable_vulkan=false angle_enable_d3d9=false angle_enable_d3d11=false angle_enable_gl=true angle_enable_desktop_glsl=true angle_enable_gl_desktop_backend=true angle_enable_gl_desktop_frontend=true angle_enable_glsl=true angle_enable_hlsl=true angle_enable_metal=false angle_enable_swiftshader=false angle_enable_null=false" --ide=vs2022