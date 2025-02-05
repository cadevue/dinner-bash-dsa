@echo off
setlocal

:: Set variables
set BUILD_DIR=build
set BIN_DIR=%BUILD_DIR%\bin
set EXECUTABLE=app.exe

:: Navigate to the bin directory
cd %BIN_DIR%

:: Check if executable exists
if exist %EXECUTABLE% (
    echo Running %EXECUTABLE%...
    %EXECUTABLE%
) else (
    echo [ERROR] Executable not found! Build the project first.
    exit /b 1
)

endlocal
