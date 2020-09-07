# libjsonnet++

set(LIBJSONNETPP_HEADERS
    ../include/libjsonnet++.h
)

set(LIBJSONNETPP_SOURCE
    libjsonnet++.cpp
)

add_library(libjsonnetpp SHARED ${LIBJSONNETPP_HEADERS} ${LIBJSONNETPP_SOURCE})
add_dependencies(libjsonnetpp jsonnet_static)
# target_link_libraries(libjsonnet libjsonnet)

# CMake prepends CMAKE_SHARED_LIBRARY_PREFIX to shared libraries, so without
# this step the output would be |liblibjsonnet|.
set_target_properties(libjsonnetpp PROPERTIES OUTPUT_NAME jsonnetpp
	VERSION     "0.16.0"
	SOVERSION   "0"
	PUBLIC_HEADER "${LIB_HEADER}")
install(TARGETS libjsonnetpp
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
target_include_directories(libjsonnetpp INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)

if (BUILD_STATIC_LIBS)
    # Static library for jsonnet command-line tool.
    add_library(libjsonnetpp_static STATIC ${LIBJSONNETPP_SOURCE})
    add_dependencies(libjsonnetpp_static jsonnet)
    target_link_libraries(libjsonnetpp_static libjsonnet_static)
    set_target_properties(libjsonnetpp_static PROPERTIES OUTPUT_NAME jsonnetpp_static)
    install(TARGETS libjsonnetpp_static DESTINATION "${CMAKE_INSTALL_LIBDIR}")
    target_include_directories(libjsonnetpp_static INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
endif()

if (BUILD_SHARED_BINARIES OR NOT BUILD_STATIC_LIBS)
    add_library(libjsonnetpp_for_binaries ALIAS libjsonnetpp)
else()
    add_library(libjsonnetpp_for_binaries ALIAS libjsonnetpp_static)
endif()

# Tests
function(add_test_executablepp test_name)
    if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/${test_name}.cpp)
        set(TEST_EXT cpp)
    else()
        set(TEST_EXT c)
    endif()
    add_executable(${test_name} ${test_name}.${TEST_EXT})

    add_dependencies(${test_name} libjsonnetpp_for_binaries libjsonnet_for_binaries GTest::Main)
    target_link_libraries(
        ${test_name} GTest::GTest GTest::Main libjsonnetpp_for_binaries libjsonnet_for_binaries)
endfunction()

if (BUILD_TESTS)
    add_test_executablepp(libjsonnetpp_test)
    # Run this in the source tree because it needs to access testdata files.
    add_test(NAME libjsonnetpp_test COMMAND ${GLOBAL_OUTPUT_PATH}/libjsonnetpp_test WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/..")
endif()
