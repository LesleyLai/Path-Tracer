cmake_minimum_required(VERSION 3.6)

project(PathTracing)

add_subdirectory(third-party)

include("cmake/compiler.cmake")
include("cmake/clangformat.cmake")
include("cmake/clang-tidy.cmake")
include("cmake/doxygen.cmake")

add_subdirectory(Project)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} common)

enable_testing ()
