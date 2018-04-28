cmake_minimum_required(VERSION 3.6)

project(PathTracing)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third-party)

include("cmake/compiler.cmake")
include("cmake/clang-tidy.cmake")
include("cmake/doxygen.cmake")

add_subdirectory(Project)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} common)

enable_testing ()
