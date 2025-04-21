cmake_minimum_required(VERSION 3.15)

# package
set(BECC_VERSION_MAJOR 0)
set(BECC_VERSION_MINOR 1)
set(BECC_VERSION_PATCH 0)
set(BECC_VERSION_RELEASE_DATE 20250421)

# package project
project(becc
    VERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
    LANGUAGES CXX
)

# option/s
## build tests, default false/OFF
option(BUILD_TESTS              "build project test/s" OFF)
## build tools, default false/OFF
option(BUILD_TOOLS              "build project tool/s" OFF)

## build tests as bool
if(BUILD_TESTS)
    set(BUILD_TESTS true)
else()
    set(BUILD_TESTS false)
endif()

## build tools as bool
if(BUILD_TOOLS)
    set(BUILD_TOOLS true)
else()
    set(BUILD_TOOLS false)
endif()

# vars
## build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

## cxx standard required
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

## cxx standard
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)

    if(MSVC)
        list(APPEND CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
endif()

# include base
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# files
## headers files
if(NOT DEFINED BEC_HEADERS_FILES)
    set(BEC_HEADERS_FILES)
endif()

## sources files
if(NOT DEFINED BEC_SOURCES_FILES)
    set(BEC_SOURCES_FILES)
endif()

list(APPEND BEC_SOURCES_FILES src/becc.cc)

# reserved

# project lib
add_library(${PROJECT_NAME} ${BEC_SOURCES_FILES})

# reserved

## warning
if(CMAKE_CXX_FLAGS STREQUAL "")
    message(WARNING "-- ${PROJECT_NAME} cxx flags is empty")
endif()


# libprcpp config
configure_file(
    ${PROJECT_SOURCE_DIR}/src/inc/becc/config.in.hh
    ${PROJECT_SOURCE_DIR}/src/inc/becc/config.hh
)

# libprcpp export
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/inc/becc/export.hh
)

# build tests
if(BUILD_TESTS)
    
endif(BUILD_TESTS)

# build tools
if(BUILD_TOOLS)
    
endif(BUILD_TOOLS)