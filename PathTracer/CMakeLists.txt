add_library(common
    include/image.hpp
    src/image.cpp
    include/color.hpp
    include/hitable.hpp
    include/vector.hpp
    include/ray.hpp
    include/sphere.hpp
    src/sphere.cpp
    include/scene.hpp
    src/scene.cpp
    )


target_include_directories(common
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

add_subdirectory(test)
enable_testing()

target_link_libraries(common stb)
