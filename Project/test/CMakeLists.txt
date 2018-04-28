include(CTest)

add_executable (PathTracingTest "")

target_sources(PathTracingTest
    PRIVATE
    camera_test.cpp
    color_test.cpp
    image_test.cpp
    vector_test.cpp
    ray_test.cpp
    sphere_test.cpp
    scene_test.cpp
    main.cpp
    )

target_link_libraries(PathTracingTest common catch2)

add_test(NAME PathTracingTest COMMAND PathTracingTest)

enable_testing()
