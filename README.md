# Bolder Render Engine
## Build Status
Master Status:
Travis: [![Travis Build Status](https://travis-ci.org/LesleyLai/Bolder-Render-Engine.svg?branch=master)](https://travis-ci.org/LesleyLai/Bolder-Render-Engine)
Appveyor: [![Build status](https://ci.appveyor.com/api/projects/status/8c6499dsh2eg1ecj/branch/master?svg=true)](https://ci.appveyor.com/project/LesleyLai/bolder-render-engine/branch/master)

Develop Statis:
Travis: [![Travis Build Status](https://travis-ci.org/LesleyLai/Bolder-Render-Engine.svg?branch=develop)](https://travis-ci.org/LesleyLai/Bolder-Render-Engine)
Appveyor: [![Build status](https://ci.appveyor.com/api/projects/status/8c6499dsh2eg1ecj/branch/develop?svg=true)](https://ci.appveyor.com/project/LesleyLai/bolder-render-engine/branch/develop)

## Build
This project requires a C++17 compiler to build. It has been tested with MSVC 2017, gcc 7, and clang 6. To build this project, you need a [CMake](https://cmake.org/) with version at least 3.8. To install third-party dependencies, you need [Conan](https://conan.io/) package manager. To successfully build the project, you need both tools installed. You can install conan through python `pip`:

``` shell
$ pip install conan # Or pip3 on some linux distributions, use sudo if nessesory
```

### Quick Start
I assume you already have a recent version of CMake and a C++17 compiler. I assume you already have a recent version of CMake and have the Conan package manager installed.

Adter installing all the tools, build the project with the following CMake instructions.

``` shell
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

## Demo scenes
### Bubbles
![bubbles.png](images/bubbles.png)
