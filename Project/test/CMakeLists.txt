include(CTest)

conan_cmake_run(REQUIRES Catch2/2.5.0@catchorg/stable
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

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

target_link_libraries("${PROJECT_NAME}Test" common CONAN_PKG::Catch2)

add_test(NAME "${PROJECT_NAME}Test" COMMAND "${PROJECT_NAME}Test")

enable_testing()
