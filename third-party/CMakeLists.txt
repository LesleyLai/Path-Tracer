# Unit test tool
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/catch")

# stb
set (STB_INCLUDE_PATH "${THIRD_PARTY_MODULE_PATH}/stb/include")

add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE "${STB_INCLUDE_PATH}")
