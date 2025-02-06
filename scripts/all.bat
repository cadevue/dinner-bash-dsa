@echo off
setlocal

:: Run clean.bat
call .\scripts\clean.bat
if %errorlevel% neq 0 (
    echo [ERROR] Clean failed!
    exit /b %errorlevel%
)

:: Run build.bat
call .\scripts\build.bat
if %errorlevel% neq 0 (
    echo [ERROR] Build failed!
    exit /b %errorlevel%
)

:: Run run.bat
call .\scripts\run.bat
if %errorlevel% neq 0 (
    echo [ERROR] Execution failed!
    exit /b %errorlevel%
)

endlocal