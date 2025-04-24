cmake_minimum_required(VERSION 3.15...3.30)

project(test_becc)

include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)

# test_base64
add_executable(test_base64 test_base64.cc)
target_link_libraries(test_base64 PRIVATE becc)