include(CTest)

add_executable (PathTracingTest "")

target_sources(PathTracingTest
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
target_link_libraries(PathTracingTest common Catch2::Catch2)

add_test(NAME PathTracingTest COMMAND PathTracingTest)

enable_testing()
