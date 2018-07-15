:: batch script for Windows build

@echo off

if "%cd%\" == "%~dp0" (
  echo Please call the script from your build folder, for instance:
  echo.
  echo cd ..
  echo mkdir build
  echo ..\niflib\build.bat
  echo.
  pause
  exit /b 1
)

cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release %~dp0
nmake
nmake package
nmake package_source
