# Travis CI runs CMake 2.8.7 so we are pinned to that verison.
cmake_minimum_required(VERSION 2.8.7)
project(jsonnet C CXX)

#include(ExternalProject)
#include(GNUInstallDirs)

# User-configurable options.
option(BUILD_JSONNET "Build jsonnet command-line tool." OFF)
option(BUILD_JSONNETFMT "Build jsonnetfmt command-line tool." OFF)
option(LIBJSONNET_BUILD_TESTS "Build and run jsonnet tests." OFF)
option(LIBJSONNET_BUILD_STATIC_LIBS "Build a static libjsonnet(Off = build dynamic lib)." ON)
#option(BUILD_SHARED_BINARIES "Link binaries to the shared libjsonnet instead of the static one." ON)
option(USE_SYSTEM_JSON "Use the system-provided json library" OFF)
set(GLOBAL_OUTPUT_PATH_SUFFIX "" CACHE STRING
    "Output artifacts directory.")

# Discourage in-source builds because they overwrite the hand-written Makefile.
# Use `cmake . -B<dir>` or the CMake GUI to do an out-of-source build.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} AND
        ${CMAKE_GENERATOR} MATCHES "Makefile")
    message(WARNING "In-source builds with the a makefile generator overwrite the handwritten Makefile. Out-of-source builds are recommended for this project.")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable CMake >3.0 warnings on Mac OS.
set(CMAKE_MACOSX_RPATH 1)

# Set output paths.
set(GLOBAL_OUTPUT_PATH "${PROJECT_BINARY_DIR}/${GLOBAL_OUTPUT_PATH_SUFFIX}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})

## Compiler flags.
#if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" OR
#        ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
#    set(OPT "-O3")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic -std=c99 -O3 ${OPT}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Woverloaded-virtual -pedantic -std=c++11 -fPIC ${OPT}")
#else()
#    # TODO: Windows support.
#    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} not supported")
#endif()

set(CMAKE_CXX_STANDARD 11)



if(USE_SYSTEM_JSON)
    find_package(nlohmann_json 3.6.1 REQUIRED)
else()
    add_subdirectory(third_party/json)
endif()

# Look for libraries in global output path.
#link_directories(${GLOBAL_OUTPUT_PATH})

# Targets

include_directories(
    include
    third_party/md5
    core
    cpp)

add_subdirectory(include)
#add_subdirectory(stdlib)
add_subdirectory(third_party/md5)
add_subdirectory(core)
add_subdirectory(cpp)
#add_subdirectory(cmd)
#add_subdirectory(test_suite)
