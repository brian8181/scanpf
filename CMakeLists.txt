# File Name:  CMakeLists.txt
# Build Date: Wed Aug 13 18:40:41 CDT 2025
# Version:    0.1.0

cmake_minimum_required(VERSION 3.2)
# We don't use the C++ compiler, so don't let project()
# test for it in case the platform doesn't have one
project(scanpf VERSION 0.1.0 LANGUAGES CXX)

# create executable
add_executable(scanpf
    src/main.cpp
    src/scanpf.cpp
)
# create executable
add_executable(scanrf
    src/main.cpp
    src/scanrf.cpp
)

# These tools are not ready yet, disable them
#[=[
add_executable(NewTool1 tool1.c)
add_executable(NewTool2
  tool2.c
  extras.c
)
]=]
