include(CTest)

add_executable ("${PROJECT_NAME}Test" "")

target_sources("${PROJECT_NAME}Test"
    PRIVATE
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
    main.cpp
    )

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries("${PROJECT_NAME}Test" common Catch2::Catch2)

add_test(NAME "${PROJECT_NAME}Test" COMMAND PathTracingTest)

enable_testing()
