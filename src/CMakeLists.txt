add_library(common
    include/aabb.hpp
    include/angle.hpp
    include/axis_aligned_rect.hpp
    src/axis_aligned_rect.cpp
    include/bounding_volume_hierarchy.hpp
    src/bounding_volume_hierarchy.cpp
    src/angle.cpp
    include/image.hpp
    src/image.cpp
    include/camera.hpp
    include/color.hpp
    include/hitable.hpp
    include/material.hpp
    src/material.cpp
    include/pathtracer.hpp
    src/pathtracer.cpp
    include/vector.hpp
    include/ray.hpp
    include/sphere.hpp
    src/sphere.cpp
    include/scene.hpp
    include/point.hpp
    include/tile.hpp
    src/scene.cpp
    )

target_include_directories(common
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

target_link_libraries(common stb  ${CONAN_LIBS})

add_subdirectory(test)
enable_testing()
