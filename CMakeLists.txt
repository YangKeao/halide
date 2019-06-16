cmake_minimum_required(VERSION 3.13)
project(halide)

set(CMAKE_CXX_STANDARD 17)

# Include LLVM

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Include PNG

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# Detect source files

aux_source_directory(src SOURCE_FILES)

add_library(halide ${SOURCE_FILES})

llvm_map_components_to_libnames(llvm_libs support core irreader ExecutionEngine Interpreter MCJIT nativecodegen X86AsmParser AsmParser)
target_link_libraries(halide ${llvm_libs} ${PNG_LIBRARY})

# Google Tests

ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} src)

aux_source_directory(tests TEST_FILES)
add_executable( runUnitTests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(runUnitTests gtest gtest_main halide)
add_test( runUnitTests runUnitTests )
