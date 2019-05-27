cmake_minimum_required(VERSION 3.13)
project(halide)

set(CMAKE_CXX_STANDARD 17)

# Include LLVM

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Detect source files

aux_source_directory(src SOURCE_FILES)

add_library(halide ${SOURCE_FILES})

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(halide ${llvm_libs})

# Google Tests

ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( runUnitTests tests/Func.cpp ${SOURCE_FILES})
target_link_libraries(runUnitTests gtest gtest_main halide)
add_test( runUnitTests runUnitTests )
