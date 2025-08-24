# File Name:  CMakeLists.txt
# Build Date: Wed Aug 13 18:40:41 CDT 2025
# Version:    0.1.0

cmake_minimum_required(VERSION 3.2)
# We don't use the C++ compiler, so don't let project()
# test for it in case the platform doesn't have one
project(scanpf VERSION 0.1.0
                DESCRIPTION "Very nice project"
                LANGUAGES CXX)

#[=[

FetchContent_Declare(
catch
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG
v2.13.6
)
# CMake 3.14+
FetchContent_MakeAvailable(catch)

]=]
set(FOO boo)

if(CMAKE_SYSTEM_NAME STREQUAL "CYGWIN")
    message(STATUS "Building under Cygwin, defining CYGWIN macro")
    add_definitions(-DCYGWIN)
endif()

find_package(fmt REQUIRED)

if(NOT fmt_FOUND)
    message(FATAL_ERROR "fmt not found")
endif()

add_executable(scanpf
    src/main.cpp
    src/scanpf.cpp
    src/regex_ext.cpp
)
target_link_libraries(scanpf PRIVATE fmt::fmt)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CPPUNIT REQUIRED cppunit)

if(NOT CPPUNIT_FOUND)
    message(FATAL_ERROR "CPPUnit not found")
endif()

add_executable(scanpf_test
            src/scanpf.cpp
    src/regex_ext.cpp
    src/scanpf_test.cpp
)

target_include_directories(scanpf_test PRIVATE ${CPPUNIT_INCLUDE_DIRS})
target_link_libraries(scanpf_test PRIVATE ${CPPUNIT_LIBRARIES})

add_executable(scanrf
        src/scanrf.cpp
        src/regex_ext.cpp
)
target_link_libraries(scanrf PRIVATE fmt::fmt)
add_executable(scanrf_test
    src/scanrf_test.cpp
)

target_include_directories(scanrf_test PRIVATE ${CPPUNIT_INCLUDE_DIRS})
target_link_libraries(scanrf_test PRIVATE ${CPPUNIT_LIBRARIES})



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
