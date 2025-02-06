@echo off
setlocal

:: Set variables
set BUILD_DIR=build

:: Remove the build directory if it exists
if exist %BUILD_DIR% (
    echo Cleaning build directory...
    rmdir /s /q %BUILD_DIR%
    echo Clean complete.
) else (
    echo No build directory found. Nothing to clean.
)

endlocal
