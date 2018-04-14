add_library(common
    include/image.hpp
    src/image.cpp
    )


target_include_directories(common
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

add_subdirectory(test)
enable_testing()

target_link_libraries(common stb)
