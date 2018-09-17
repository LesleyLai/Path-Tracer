# Bolder Render Engine
## Build Status
Master Status:
Travis: [![Travis Build Status](https://travis-ci.org/LesleyLai/Bolder-Render-Engine.svg?branch=master)](https://travis-ci.org/LesleyLai/Bolder-Render-Engine)
Appveyor: [![Build status](https://ci.appveyor.com/api/projects/status/8c6499dsh2eg1ecj/branch/master?svg=true)](https://ci.appveyor.com/project/LesleyLai/bolder-render-engine/branch/master)

Develop Statis:
Travis: [![Travis Build Status](https://travis-ci.org/LesleyLai/Bolder-Render-Engine.svg?branch=develop)](https://travis-ci.org/LesleyLai/Bolder-Render-Engine)
Appveyor: [![Build status](https://ci.appveyor.com/api/projects/status/8c6499dsh2eg1ecj/branch/develop?svg=true)](https://ci.appveyor.com/project/LesleyLai/bolder-render-engine/branch/develop)

## Build
This project requires a C++17 compiler to build. It has been tested with MSVC 2017, gcc 7, and clang 6. To build this project, you need a [CMake](https://cmake.org/) with version at least 3.8. To install third-party dependencies, you need [Vcpkg](https://github.com/Microsoft/vcpkg).

### Quick Start
I assume you already have a recent version of CMake and a C++17 compiler. I assume you already have a recent version of CMake and a C++17 compiler. After those, the first thing you should do is installing Vcpkg following the instruction [here](https://github.com/Microsoft/vcpkg).

To install dependencies:
```
./vcpkg install catch2
```

Then go to the folder of this project and puts:

``` shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
make
```

Note we need to pass the toolchain file of vcpkg to CMake as an argument.

## Demo
![bubbles.png](images/bubbles.png)
