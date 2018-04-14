add_executable (PathTracerTest "")

target_sources(PathTracerTest
    PRIVATE
    image_test.cpp
    main.cpp
    )

target_link_libraries(PathTracerTest common catch2)

add_test(NAME PathTracerTest COMMAND PathTracerTest)

enable_testing()
