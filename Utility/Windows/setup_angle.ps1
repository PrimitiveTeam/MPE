# Set working directory to the directory of the script
$SCRIPT_DIR = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

Write-Host "Setting up directories..."
New-Item -Path "$SCRIPT_DIR\..\..\Vendor\WIN32" -ItemType Directory -Force

# CD into Vendor
Set-Location -Path "$SCRIPT_DIR\..\..\Vendor\WIN32"

# Check if "angle" directory already exists
if (Test-Path -Path "angle") {
    Write-Host "angle already exists. Skipping..."
}
else {
    Write-Host "Cloning angle..."
    git clone https://chromium.googlesource.com/angle/angle
    Set-Location -Path "angle"
}

Write-Host "Bootstrapping angle..."
python scripts/bootstrap.py
gclient sync

Write-Host "Generating Build Files for Release and Debug"
New-Item -Path "out/Release" -ItemType Directory -Force

gn gen out/Release `
    --args='
    is_component_build=false
    target_cpu=x64
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
    ' `
    --ide=vs2022

Write-Host "Building angle"
autoninja -C out/Release

# gn gen out/Release --args="is_component_build=false is_debug=false angle_enable_vulkan=false angle_enable_d3d9=false angle_enable_d3d11=false angle_enable_gl=true angle_enable_metal=false angle_enable_swiftshader=false angle_enable_null=false" --ide=vs2022
# # ninja -C out/Release
# gn gen out/Release --args="is_component_build=false is_debug=false angle_enable_vulkan=false angle_enable_d3d9=false angle_enable_d3d11=false angle_enable_gl=true angle_enable_desktop_glsl=true angle_enable_gl_desktop_backend=true angle_enable_gl_desktop_frontend=true angle_enable_glsl=true angle_enable_hlsl=true angle_enable_metal=false angle_enable_swiftshader=false angle_enable_null=false" --ide=vs2022

# For terminal / VERIFIED
# gn gen out/Release --args='is_component_build=true is_debug=false angle_assert_always_on=true angle_enable_d3d9=false angle_enable_d3d11=false angle_enable_gl=true angle_enable_metal=false angle_enable_null=false angle_enable_vulkan=false angle_enable_essl=true angle_enable_glsl=true' --ide=vs2022

# gn gen out/Release `
# --args='
# is_component_build=false
# target_cpu=x64
# is_debug=false
# angle_assert_always_on=true
# angle_enable_d3d9=false
# angle_enable_d3d11=false
# angle_enable_gl=true
# angle_enable_metal=false
# angle_enable_null=false
# angle_enable_vulkan=false
# angle_enable_essl=true
# angle_enable_glsl=true
# angle_enable_desktop_glsl=true
# angle_enable_gl_desktop_backend=true
# angle_enable_gl_desktop_frontend=true
# angle_enable_hlsl=true
# angle_enable_swiftshader=false
# ' `
# --ide=vs2022