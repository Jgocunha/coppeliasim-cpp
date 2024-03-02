@echo off

set PROJECT_ROOT=%CD%

:: Create build folders
mkdir %PROJECT_ROOT%\build\x64-release
mkdir %PROJECT_ROOT%\build\x64-debug

:: Run CMake
cmake -G "Visual Studio 17 2022" -A x64 -S "%PROJECT_ROOT%" -B "%PROJECT_ROOT%\build\x64-release" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release

:: Build your project using the generated build files 
cmake --build "%PROJECT_ROOT%\build\x64-release" --config Release

:: Run CMake
cmake -G "Visual Studio 17 2022" -A x64 -S "%PROJECT_ROOT%" -B "%PROJECT_ROOT%\build\x64-debug" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug

:: Build your project using the generated build files 
cmake --build "%PROJECT_ROOT%\build\x64-debug" --config Debug


:: Optionally, you can run your executable here if applicable

pause
exit /b 1

