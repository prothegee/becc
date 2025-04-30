cmake_minimum_required(VERSION 3.15)

# package
set(BECC_VERSION_MAJOR 0)
set(BECC_VERSION_MINOR 10)
set(BECC_VERSION_PATCH 0)
set(BECC_VERSION_RELEASE_DATE 20250501)

# package project
project(becc
    VERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
    DESCRIPTION "module library treatment for cpp backend project"
    HOMEPAGE_URL "https://github.com/prothegee/becc"
    LANGUAGES CXX C
)

# option/s
## build tests, default false/OFF
option(BUILD_TESTS              "build project test/s" OFF)
## build tools, default false/OFF
option(BUILD_TOOLS              "build project tool/s" OFF)
## build vendor stb
option(BUILD_VENDOR_STB         "build vendor stb" OFF)
## build vendor sdl
option(BUILD_VENDOR_SDL3        "build vendor sdl3" OFF)
## build vendor haru
option(BUILD_VENDOR_HARU        "build vendor haru" OFF)
## build vendor nanosvg
option(BUILD_VENDOR_NANOSVG     "build vendor nanosvg" OFF)
## build vendor zxing-cpp
option(BUILD_VENDOR_ZXING_CPP   "build vendor zxing-cpp" OFF)

## rules of options

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

## build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

## cxx standard required
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
## cxx extensions
if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


## cxx standard
### by default build is set for gnu linux environment
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # Automatic standard detection from compiler flags
    set(_detected_standard 17)
    
    # Check for Unix-style flags (-std=c++XX or -std=gnu++XX)
    string(REGEX MATCH "-std=([c|gnu]\\+\\+)([0-9]+)" _ "${CMAKE_CXX_FLAGS}")
    if(CMAKE_MATCH_2)
        set(_detected_standard ${CMAKE_MATCH_2})
    endif()
    
    # Check for MSVC flags (/std:c++XX or /std:c++latest)
    if(NOT _detected_standard AND MSVC)
        string(REGEX MATCH "/std:c\\+\\+latest" _ "${CMAKE_CXX_FLAGS}")
        if(CMAKE_MATCH_0)
            set(_detected_standard 20) # Map /std:c++latest to C++20
        else()
            string(REGEX MATCH "/std:c\\+\\+([0-9]+)" _ "${CMAKE_CXX_FLAGS}")
            if(CMAKE_MATCH_1)
                set(_detected_standard ${CMAKE_MATCH_1})
            endif()
        endif()
    endif()
    
    set(CMAKE_CXX_STANDARD ${_detected_standard} CACHE STRING "C++ standard to use (17, 20, etc.)")
else()
    set(CMAKE_CXX_STANDARD "${CMAKE_CXX_STANDARD}" CACHE STRING "C++ standard to use (17, 20, etc.)" FORCE)
endif()

## cxx flags
### by default build is set for gnu linux environment
if(NOT DEFINED CMAKE_CXX_FLAGS)
    if(MSVC)
        if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
            list(APPEND CMAKE_CXX_FLAGS "/std:c++latest")
        else()
            list(APPEND CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
        endif()
    else()
        list(APPEND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
else()
    # Clean existing standard flags
    string(REGEX REPLACE "-std=[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/std:c\\+\\+[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    
    # Add correct standard flag
    if(MSVC)
        if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
            list(APPEND CMAKE_CXX_FLAGS "/std:c++latest")
        else()
            list(APPEND CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
        endif()
    else()
        list(APPEND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
endif()

## rest of the world is debug except Release
set(BECC_IS_DEBUG true)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BECC_IS_DEBUG false) 
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(BECC_IS_DEBUG false) 
endif()

## system name
if(NOT DEFINED BECC_SYSTEM_NAME)
    set(BECC_SYSTEM_NAME "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_NAME}" BECC_SYSTEM_NAME)
### rules of os
if(${BECC_SYSTEM_NAME} STREQUAL "macos")
    set(BECC_SYSTEM_NAME "osx")
elseif(${BECC_SYSTEM_NAME} STREQUAL "darwin")
    set(BECC_SYSTEM_NAME "osx")
else()
    # force otherwise
    string(TOLOWER "${CMAKE_SYSTEM_NAME}" BECC_SYSTEM_NAME)
endif()

## system process
if(NOT DEFINED BECC_SYSTEM_PROCESSOR)
    set(BECC_SYSTEM_PROCESSOR "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" BECC_SYSTEM_PROCESSOR)

# include base
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# files
## headers files
if(NOT DEFINED BEC_HEADERS_FILES)
    set(BEC_HEADERS_FILES)
endif()
## constants
set(BEC_HEADERS_FILES_CONSTANTS
    src/inc/becc/constants/string_const.hh
)
list(APPEND BEC_HEADERS_FILES ${BEC_HEADERS_FILES_CONSTANTS})
## enums
## functions
set(BEC_HEADERS_FILES_FUNCTIONS
    src/inc/becc/functions/communication.hh
    src/inc/becc/functions/cryptography.hh
    src/inc/becc/functions/date_and_time.hh
    src/inc/becc/functions/generate.hh
    src/inc/becc/functions/system.hh
    src/inc/becc/functions/utility.hh
)
list(APPEND BEC_HEADERS_FILES ${BEC_HEADERS_FILES_FUNCTIONS})
## interfaces
set(BEC_HEADERS_FILES_INTERFACES
    src/inc/becc/interfaces/ipostgresql_core_interface.hh
    src/inc/becc/interfaces/iscylladb_core_interface.hh
)
list(APPEND BEC_HEADERS_FILES ${BEC_HEADERS_FILES_INTERFACES})
## modules
## types
set(BEC_HEADERS_FILES_TYPES
    src/inc/becc/types/auth_type.hh
    src/inc/becc/types/look_type.hh
)
list(APPEND BEC_HEADERS_FILES ${BEC_HEADERS_FILES_TYPES})

## sources files
if(NOT DEFINED BEC_SOURCES_FILES)
    set(BEC_SOURCES_FILES)
endif()

list(APPEND
    BEC_SOURCES_FILES
        src/becc.cc
        # constants
        # enums
        # functions
        src/communication.cc
        src/cryptography.cc
        src/date_and_time.cc
        src/generate.cc
        src/system.cc
        src/utility.cc
        # interfaces
        src/ipostgresql_core_interface.cc
        src/iscylladb_core_interface.cc
        # modules
)

# packages, lib related
## 
## base toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- ${PROJECT_NAME}: using CMAKE_TOOLCHAIN_FILE as `${CMAKE_TOOLCHAIN_FILE}`")
endif()
##
## reserved: package manager?
##
## curl executeable
set(BECC_USING_CURL_EXECUTEABLE false)
set(BECC_USING_CURL_EXECUTEABLE_PATH)
if(MSVC)
    find_file(BECC_USING_CURL_EXECUTEABLE_PATH "curl.exe")
else()
    # assume unix stlye
    find_file(BECC_USING_CURL_EXECUTEABLE_PATH "curl")
endif()
if(BECC_USING_CURL_EXECUTEABLE_PATH)
    set(BECC_USING_CURL_EXECUTEABLE true)
    message(NOTICE "-- ${PROJECT_NAME}: curl found in \"${BECC_USING_CURL_EXECUTEABLE_PATH}\"")
endif()
##
## jsoncpp
set(BECC_USING_JSONCPP false)

find_package(jsoncpp CONFIG)
if(jsoncpp_FOUND)
    set(BECC_USING_JSONCPP true)
    set(BECC_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}: adding jsoncpp since package found")
endif()
##
## openssl
set(BECC_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(BECC_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}: adding openssl since package found")
endif()
##
## drogon
set(BECC_USING_DROGON false)

find_package(Drogon CONFIG)
if(Drogon_FOUND)
    set(BECC_USING_DROGON true)
    message(NOTICE "-- ${PROJECT_NAME}: adding drogon since package found")
endif()
##
## argon2
set(BECC_USING_ARGON2 false)
set(BECC_ARGON2_HEADER)
set(BECC_ARGON2_SHARED)
set(BECC_ARGON2_LIBRARY)

find_file(BECC_ARGON2_HEADER "argon2.h")
if(WIN32)
    find_file(BECC_ARGON2_SHARED "argon2.dll")
    find_file(BECC_ARGON2_LIBRARY "argon2.lib")
else()
    find_file(BECC_ARGON2_LIBRARY "libargon2.so")
    find_file(BECC_ARGON2_LIBRARY "libargon2.a")
endif()

if(BECC_ARGON2_HEADER AND BECC_ARGON2_SHARED AND BECC_ARGON2_LIBRARY)
    set(BECC_USING_ARGON2 true)
    message(NOTICE "-- ${PROJECT_NAME}: adding argon2 since header, shared & lib found")
endif()
##
## postgresql
set(BECC_USING_POSTGRESQL false)

find_package(PostgreSQL)
if(PostgreSQL_FOUND)
    set(BECC_USING_POSTGRESQL true)
    message(NOTICE "-- ${PROJECT_NAME}: adding postgresql since package found")
endif()
##
## scylladb
set(BECC_USING_SCYLLADB false)
set(BECC_CASSANDRA_HEADER)
set(BECC_SCYLLA_EXECUTEABLE)

if(LINUX)
    find_file(BECC_CASSANDRA_HEADER "cassandra.h")
    find_file(BECC_SCYLLA_EXECUTEABLE "scylla")

    if(BECC_CASSANDRA_HEADER AND BECC_SCYLLA_EXECUTEABLE)
        set(BECC_USING_SCYLLADB true)
        message(NOTICE "-- ${PROJECT_NAME}: adding scylladb since deps found")
    endif()
else()
    message(NOTICE "-- ${PROJECT_NAME}: skipping scylladb deps, system not supported")
endif()
##
## stb
set(BECC_USING_STB false)

if(BUILD_VENDOR_STB)
    if(NOT DEFINED ${Stb_INCLUDE_DIR})
        set(Stb_INCLUDE_DIR "")
    endif()

    set(BECC_VENDOR_STB_DIR "${PROJECT_SOURCE_DIR}/vendors/stb")

    if(NOT ${BECC_VENDOR_STB_DIR} STREQUAL "")
        set(BECC_USING_STB true)
        set(Stb_INCLUDE_DIR ${BECC_VENDOR_STB_DIR})
        include_directories(${Stb_INCLUDE_DIR})
    endif()

    set(BECC_USING_STB true)
    message(NOTICE "-- ${PROJECT_NAME}: adding stb")
endif()
##
## sdl3
set(BECC_USING_SDL3 false)

if(BUILD_VENDOR_SDL3)
    set(BECC_VENDOR_SDL3_DIR "${PROJECT_SOURCE_DIR}/vendors/sdl3")

    include_directories(${BECC_VENDOR_SDL3_DIR}/include)

    link_directories(AFTER "${CMAKE_BINARY_DIR}/BECC_SDL3")

    set(SDL_STATIC true)
    set(SDL_TEST_LIBRARY false)

    add_subdirectory(${BECC_VENDOR_SDL3_DIR} BECC_SDL3)

    set(BECC_USING_SDL3 true)
    message(NOTICE "-- ${PROJECT_NAME}: adding sdl3")
endif()
##
## haru
set(BECC_USING_HARU false)

if(BUILD_VENDOR_HARU)
    # set(LIBHPDF_EXAMPLES OFF CACHE BOOL "Disable examples" FORCE) # disable example warning cmp policy for haru
    # cmake_policy(SET CMP0077 NEW)

    set(BECC_VENDOR_LIBHARU_DIR "${PROJECT_SOURCE_DIR}/vendors/libharu")

    set(BECC_VENDOR_LIBHARU_DIR_SOURCE_OUT ${CMAKE_BINARY_DIR}/BECC_LIBHARU/src)
    set(BECC_VENDOR_LIBHARU_DIR_INCLUDE_OUT ${CMAKE_BINARY_DIR}/BECC_LIBHARU/include)

    set(LIBHPDF_SHARED false)
    set(LIBHPDF_STATIC true)
    set(LIBHPDF_EXAMPLES false)

    include_directories(${BECC_VENDOR_LIBHARU_DIR}/include)

    include_directories(${BECC_VENDOR_LIBHARU_DIR_SOURCE_OUT})
    include_directories(${BECC_VENDOR_LIBHARU_DIR_INCLUDE_OUT})

    link_directories(AFTER "${BECC_VENDOR_LIBHARU_DIR_SOURCE_OUT}")

    add_subdirectory(${BECC_VENDOR_LIBHARU_DIR} BECC_LIBHARU)

    set(BECC_USING_HARU true)
    message(NOTICE "-- ${PROJECT_NAME}: adding haru hpdf")
endif()
##
## nanosvg
set(BECC_USING_NANOSVG false)

if(BUILD_VENDOR_NANOSVG)
    set(BECC_VENDOR_NANOSVG_DIR "${PROJECT_SOURCE_DIR}/vendors/nanosvg")

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")
    endif()

    set(BECC_VENDOR_NANOSVG_DIR_NANOSVG)

    file(COPY "${BECC_VENDOR_NANOSVG_DIR}/src/" DESTINATION "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")

    set(BECC_VENDOR_NANOSVG_DIR_NANOSVG "${CMAKE_BINARY_DIR}/BECC_NANOSVG")

    include_directories(${BECC_VENDOR_NANOSVG_DIR_NANOSVG})

    add_subdirectory(${BECC_VENDOR_NANOSVG_DIR} BECC_NANOSVG)
    set(BECC_USING_NANOSVG true)
    message(NOTICE "-- ${PROJECT_NAME}: adding nanosvg")
endif()
##
## zxing-cpp
set(BECC_USING_ZXING_CPP false)

if(BUILD_VENDOR_ZXING_CPP)
    set(BECC_VENDOR_ZXING_CPP_DIR "${PROJECT_SOURCE_DIR}/vendors/zxing-cpp")

    set(ZXING_EXPERIMENTAL_API true)
    set(ZXING_EXAMPLES false)
    set(ZXING_BLACKBOX_TESTS false)
    set(ZXING_UNIT_TESTS false)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")
    endif()

    set(BECC_VENDOR_ZXING_CPP_DIR_ZXING)

    file(COPY "${BECC_VENDOR_ZXING_CPP_DIR}/core/src/" DESTINATION "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")

    set(BECC_VENDOR_ZXING_CPP_DIR_ZXING_DIR "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP")

    include_directories(${BECC_VENDOR_ZXING_CPP_DIR_ZXING_DIR})

    add_subdirectory(${BECC_VENDOR_ZXING_CPP_DIR} BECC_ZXING_CPP)
    set(BECC_USING_ZXING_CPP true)
    message(NOTICE "-- ${PROJECT_NAME}: adding zxing-cpp")
endif()

# project lib
add_library(${PROJECT_NAME} ${BEC_SOURCES_FILES})

# target libs, package, & executeable
##
## jsoncpp
if(BECC_USING_JSONCPP)
    # target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_JSONCPP_DIR_INCLUDE})

    target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp)
endif()
##
## openssl
if(BECC_USING_OPENSSL)
    # target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_OPENSSL_DIR_INCLUDE_BUILD})
    # target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_OPENSSL_DIR_INCLUDE_SRC})

    # if(MSVC) # windows, why?
    #     target_link_libraries(${PROJECT_NAME} PRIVATE 
    #         "${CMAKE_BINARY_DIR}/_deps/openssl-source-build/libcrypto.lib"
    #         "${CMAKE_BINARY_DIR}/_deps/openssl-source-build/libssl.lib"
    #     )
    # else()
    #     target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    # endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()
##
## drogon
if(BECC_USING_DROGON)
    target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
endif()
##
## argon2
if(BECC_USING_ARGON2)
    target_link_libraries(${PROJECT_NAME} PRIVATE argon2)
endif()
##
## postgresql
if(BECC_USING_POSTGRESQL)
    target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
endif()
##
## scylladb
if(BECC_USING_SCYLLADB)
    target_link_libraries(${PROJECT_NAME} PRIVATE scylla-cpp-driver)
endif()
##
## stb
if(BECC_USING_STB)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
endif()
##
## sdl
if(BECC_USING_SDL3)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-static SDL_uclibc SDL3_Headers)
endif()
##
## haru
if(BECC_USING_HARU)
    target_link_libraries(${PROJECT_NAME} PRIVATE hpdf)

    target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_SOURCE_OUT})
    target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_INCLUDE_OUT})
endif()
##
## nanosvg
if(BECC_USING_NANOSVG)
    target_link_libraries(${PROJECT_NAME} PRIVATE nanosvg nanosvgrast)
endif()
##
## zxing-cpp
if(BECC_USING_ZXING_CPP)
    target_link_libraries(${PROJECT_NAME} PRIVATE ZXing::Core ZXing::ZXing)
endif()

## installed options
### reserved

# compiler options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(BECC_COMPILER_ID    1)
    set(BECC_COMPILER_GNU   true)
    set(BECC_COMPILER_MSVC  false)
    set(BECC_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-empty-body
        -Wno-unused-function
        -Wno-deprecated-declarations
        -lm
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(BECC_COMPILER_ID    2)
    set(BECC_COMPILER_GNU   false)
    set(BECC_COMPILER_MSVC  true)
    set(BECC_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /wd4996
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(BECC_COMPILER_ID    3)
    set(BECC_COMPILER_GNU   false)
    set(BECC_COMPILER_MSVC  false)
    set(BECC_COMPILER_CLANG true)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-dynamic-class-memaccess
        -Wno-unused-private-field
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-null-conversion
        -Wno-empty-body
        -Wno-unused-lambda-capture
        -Wno-unused-function
        -Wno-tautological-constant-out-of-range-compare
        -Wno-deprecated-declarations
    )
else()
    set(BECC_COMPILER_ID    0)
    set(BECC_COMPILER_GNU   false)
    set(BECC_COMPILER_MSVC  false)
    set(BECC_COMPILER_CLANG false)

    message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
endif()

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

# target include dirs
## core include: src/inc
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/inc
)

# target source
## dont expand this yet
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# build tests
if(BUILD_TESTS)
    add_subdirectory(tests BECC_TESTS)
endif(BUILD_TESTS)

# build tools
if(BUILD_TOOLS)
    
endif(BUILD_TOOLS)