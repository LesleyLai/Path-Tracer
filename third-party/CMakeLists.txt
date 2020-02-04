# stb
add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb/include")

# indicators
add_subdirectory(indicators)
#add_library(indicators INTERFACE)
#target_include_directories(indicators SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/indicators/include")
