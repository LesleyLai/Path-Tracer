include(CTest)

add_executable ("${PROJECT_NAME}Test"
    aabb_test.cpp
    angle_test.cpp
    camera_test.cpp
    color_test.cpp
    image_test.cpp
    point_test.cpp
    vector_test.cpp
    ray_test.cpp
    sphere_test.cpp
    scene_test.cpp
    tile_test.cpp
    main.cpp)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries("${PROJECT_NAME}Test" common)

add_test(NAME "${PROJECT_NAME}Test" COMMAND "${PROJECT_NAME}Test")

enable_testing()
