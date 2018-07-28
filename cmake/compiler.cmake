# Compiler specific settings

if(compiler_included)
    return()
endif()
set(compiler_included true)

function(add_compiler_flags)
    foreach(flag ${ARGV})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
    endforeach()
endfunction()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compiler_flags(/std:c++latest) # force standard conformance
else()
    set (CMAKE_CXX_STANDARD 17)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)
endif()


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compiler_flags(-Wall)
    add_compiler_flags(-Wextra)
    add_compiler_flags(-Wno-sign-compare)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS) # Suppress C4996

    if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10)
        add_compiler_flags(/permissive-) # force standard conformance
    endif()
endif()
