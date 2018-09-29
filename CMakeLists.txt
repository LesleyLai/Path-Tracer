cmake_minimum_required(VERSION 3.8)

project(BolderRenderEngine)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(external)

include("cmake/compiler.cmake")
include("cmake/doxygen.cmake")

add_subdirectory(src)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} common)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

enable_testing ()
