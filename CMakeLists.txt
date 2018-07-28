cmake_minimum_required(VERSION 3.8)

project(PathTracing)

add_subdirectory(third-party)

include("cmake/compiler.cmake")
include("cmake/doxygen.cmake")

add_subdirectory(Project)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} common)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

enable_testing ()
