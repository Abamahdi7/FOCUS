@echo off
setlocal
cd /d "%~dp0"

if exist Focus.exe (
    Focus.exe
    pause
    exit /b 0
)

where cl >nul 2>nul
if %errorlevel%==0 (
    cl /nologo /EHsc /std:c++17 /utf-8 /Iinclude main.cpp src\*.cpp /Fe:Focus.exe
    if exist Focus.exe Focus.exe
    pause
    exit /b 0
)

where g++ >nul 2>nul
if %errorlevel%==0 (
    g++ -std=c++17 -Iinclude main.cpp src\*.cpp -o Focus.exe
    if exist Focus.exe Focus.exe
    pause
    exit /b 0
)

echo No C++ compiler found in PATH.
echo Open Developer PowerShell for Visual Studio, then run:
echo cl /EHsc /std:c++17 /utf-8 /Iinclude main.cpp src\*.cpp /Fe:Focus.exe
pause
