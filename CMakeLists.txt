# File Name:  CMakeLists.txt
# Build Date: Wed Aug 13 18:40:41 CDT 2025
# Version:    0.1.0

cmake_minimum_required(VERSION 3.2)
# We don't use the C++ compiler, so don't let project()
# test for it in case the platform doesn't have one
project(scanpf VERSION 0.1.0
                DESCRIPTION "Very nice project"
                LANGUAGES CXX)

set(FOO boo)

#target_link_libraries(another PUBLIC one)

add_executable(scanpf
    src/main.cpp
    src/scanpf.cpp
    src/regex_ext.cpp
)
#[=[
add_executable(scanpf_test
    src/main.cpp
    src/scanpf.cpp
    src/regex_ext.cpp
    src/scanpf_test.cpp
)
]=]
add_executable(scanrf
    src/main.cpp
    src/scanrf.cpp
    src/regex_ext.cpp
)
#[=[
add_executable(scanrf_test
    src/main.cpp
    src/scanpf.cpp
    src/regex_ext.cpp
    src/scanrf_test.cpp
)
]=]

#[=[
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Enable C++11 for GNU compilers
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON  )

endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Enable C++11 for GNU compilers
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON  )
]=]

# These tools are not ready yet, disable them
#[=[
add_executable(NewTool1 tool1.c)
add_executable(NewTool2
  tool2.c
  extras.c
)
]=]
