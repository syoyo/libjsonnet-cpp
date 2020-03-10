cmake_minimum_required(VERSION 3.1)
project(test C CXX)

# libjsonnet-cpp
add_subdirectory(../../ build_libjsonnet_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(simple main.cc)
target_include_directories(simple PRIVATE ../../include)
target_link_libraries(simple PRIVATE libjsonnet++)
