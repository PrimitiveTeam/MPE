@echo on
setlocal enabledelayedexpansion

SET SCRIPT_DIR=%~dp0

:: Path to clang-format executable
set CLANG_FORMAT=clang-format

:: Path to the .clang-format file
set CLANG_FORMAT_FILE=%SCRIPT_DIR%..\.clang-format

:: Path to the file containing directory paths
set DIR_LIST=%SCRIPT_DIR%..\.dirs_to_format

:: Read each line in .dirs_to_format, prepend ../../, and format files in those directories
for /f "tokens=*" %%d in (%DIR_LIST%) do (
    set "DIR_PATH=%SCRIPT_DIR%../../%%d"
    if exist "!DIR_PATH!" (
        for %%f in (!DIR_PATH!\*.h !DIR_PATH!\*.hpp !DIR_PATH!\*.c !DIR_PATH!\*.cpp) do (
            %CLANG_FORMAT% -style=file:%CLANG_FORMAT_FILE% -i "%%f"
        )
    ) else (
        echo Directory not found: !DIR_PATH!
    )
)

echo All files formatted.