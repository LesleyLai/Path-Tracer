# Unit test tool
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/catch")

# stb
add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb/include")
