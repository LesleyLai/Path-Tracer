cmake_minimum_required(VERSION 3.8)

project(PathTracer)

add_subdirectory(third-party)

# Conan package manager
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)


conan_add_remote(NAME bincrafters INDEX 1
    URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include("cmake/compiler.cmake")
include("cmake/doxygen.cmake")

add_subdirectory(Project)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} common)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

enable_testing ()
