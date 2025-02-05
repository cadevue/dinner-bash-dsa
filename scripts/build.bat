@echo off
setlocal

:: Set variables
set BUILD_DIR=build
set BIN_DIR=%BUILD_DIR%\bin
set EXECUTABLE=app.exe
set GENERATOR="MinGW Makefiles"

:: Create build directory if it doesn't exist
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: Navigate to build directory and generate CMake files
cd %BUILD_DIR%
cmake -G %GENERATOR% ..

:: Build the project
if %errorlevel% neq 0 (
    echo [ERROR] CMake configuration failed!
    exit /b %errorlevel%
)
make

:: Check if build succeeded
if %errorlevel% neq 0 (
    echo [ERROR] Build failed!
    exit /b %errorlevel%
)

echo Build completed successfully.
endlocal
