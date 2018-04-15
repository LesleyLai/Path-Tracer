add_executable (PathTracingTest "")

target_sources(PathTracingTest
    PRIVATE
    image_test.cpp
    vector_test.cpp
    ray_test.cpp
    main.cpp
    )

target_link_libraries(PathTracingTest common catch2)

add_test(NAME PathTracingTest COMMAND PathTracerTest)

enable_testing()
