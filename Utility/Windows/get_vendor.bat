@echo off
REM Set working directory to the directory of the script
SET SCRIPT_DIR=%~dp0

echo Setting up directories...
mkdir %SCRIPT_DIR%..\..\Vendor

REM CD into Vendor
cd %SCRIPT_DIR%..\..\Vendor
echo Generating GLAD for OpenGL version 4.6...
glad --quiet --api gl:compatibility=4.6 --out-path .\Glad c

REM imgui
REM If imgui already exists, cancel next step
if exist "imgui" (
    echo imgui already exists. Skipping...
    exit /b 0
) else (
    echo Cloning imgui...
    git clone https://github.com/ocornut/imgui.git
    cd imgui
    git checkout docking
)

echo Setup complete.
