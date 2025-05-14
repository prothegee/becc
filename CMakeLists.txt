cmake_minimum_required(VERSION 3.15)

# package
set(BECC_VERSION_MAJOR 0)
set(BECC_VERSION_MINOR 17)
set(BECC_VERSION_PATCH 2)
set(BECC_VERSION_RELEASE_DATE 20250514)

# package project
project(becc
    VERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
    DESCRIPTION "module library treatment for cpp backend project"
    HOMEPAGE_URL "https://github.com/prothegee/becc"
    LANGUAGES CXX
)

# option/s
## build tests, default false/OFF
option(BECC_BUILD_TESTS                         "build project test/s" OFF)
## build tools, default false/OFF
option(BECC_BUILD_TOOLS                         "build project tool/s" OFF)
## build vendor stb, default false/OFF
option(BECC_BUILD_VENDOR_STB                    "build vendor stb" OFF)
## build vendor sdl, default false/OFF
option(BECC_BUILD_VENDOR_SDL3                   "build vendor sdl3" OFF)
## build vendor haru, default false/OFF
option(BECC_BUILD_VENDOR_HARU                   "build vendor haru" OFF)
## build vendor nanosvg, default false/OFF
option(BECC_BUILD_VENDOR_NANOSVG                "build vendor nanosvg" OFF)
## build vendor zxing-cpp, default false/OFF
option(BECC_BUILD_VENDOR_ZXING_CPP              "build vendor zxing-cpp" OFF)
## build vendor couchbase-cxx-client, default false/OFF
option(BECC_BUILD_VENDOR_COUCHBASE_CXX_CLIENT   "build vendor couchbase-client-cxx" OFF)

### build use vcpkg, default false/OFF
option(BECC_BUILD_VCPKG                         "build use vcpkg" OFF)
### build vcpkg_triplet, default false/OFF, should be string value
option(BECC_BUILD_VCPKG_TRIPLET                 "build triplet for vcpkg" OFF)

## rules of options

## build tests as bool
if(BECC_BUILD_TESTS)
    set(BECC_BUILD_TESTS true)
else()
    set(BECC_BUILD_TESTS false)
endif()

## build tools as bool
if(BECC_BUILD_TOOLS)
    set(BECC_BUILD_TOOLS true)
else()
    set(BECC_BUILD_TOOLS false)
endif()

## build vcpkg as bool
if(BECC_BUILD_VCPKG)
    set(BECC_BUILD_VCPKG true)
else()
    set(BECC_BUILD_VCPKG false)
endif()

## build type
if(NOT CMAKE_BECC_BUILD_TYPE)
    set(CMAKE_BECC_BUILD_TYPE "Debug")
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
    # automatic standard detection from compiler flags
    set(_detected_standard 17)
    # check for Unix-style flags (-std=c++XX or -std=gnu++XX)
    string(REGEX MATCH "-std=([c|gnu]\\+\\+)([0-9]+)" _ "${CMAKE_CXX_FLAGS}")
    if(CMAKE_MATCH_2)
        set(_detected_standard ${CMAKE_MATCH_2})
    endif()
    # check for MSVC flags (/std:c++XX or /std:c++latest)
    if(NOT _detected_standard AND MSVC)
        string(REGEX MATCH "/std:c\\+\\+latest" _ "${CMAKE_CXX_FLAGS}")
        if(CMAKE_MATCH_0)
            set(_detected_standard latest) # map /std:c++latest to C++20
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
            set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
        else()
            set(CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD} /EHsc")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
else()
    # clean existing flags
    string(REGEX REPLACE "-std=[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/std:c\\+\\+[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/EH[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # remove old /EH flags
    string(REPLACE "/MP" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")  # remove /MP
    if(MSVC)
        if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
            set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
        else()
            set(CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD} /EHsc")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
endif()

## rest of the world is debug except Release
set(BECC_IS_DEBUG true)
if(CMAKE_BECC_BUILD_TYPE STREQUAL "Release")
    set(BECC_IS_DEBUG false) 
elseif(CMAKE_BECC_BUILD_TYPE STREQUAL "MinSizeRel")
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
if(NOT DEFINED BECC_HEADERS_FILES)
    set(BECC_HEADERS_FILES)
endif()
### constants
set(BECC_HEADERS_FILES_CONSTANTS
    src/inc/becc/constants/string_const.hh
)
list(APPEND BECC_HEADERS_FILES ${BECC_HEADERS_FILES_CONSTANTS})
### enums
### functions
set(BECC_HEADERS_FILES_FUNCTIONS
    src/inc/becc/functions/communication.hh
    src/inc/becc/functions/cryptography.hh
    src/inc/becc/functions/date_and_time.hh
    src/inc/becc/functions/generate.hh
    src/inc/becc/functions/system.hh
    src/inc/becc/functions/utility.hh
)
list(APPEND BECC_HEADERS_FILES ${BECC_HEADERS_FILES_FUNCTIONS})
### interfaces
set(BECC_HEADERS_FILES_INTERFACES
    src/inc/becc/interfaces/ipostgresql_core_interface.hh
    src/inc/becc/interfaces/iscylladb_core_interface.hh
)
list(APPEND BECC_HEADERS_FILES ${BECC_HEADERS_FILES_INTERFACES})
### modules
### types
set(BECC_HEADERS_FILES_TYPES
    src/inc/becc/types/auth_type.hh
    src/inc/becc/types/look_type.hh
)
list(APPEND BECC_HEADERS_FILES ${BECC_HEADERS_FILES_TYPES})

## sources files
if(NOT DEFINED BECC_SOURCES_FILES)
    set(BECC_SOURCES_FILES)
endif()

list(APPEND
    BECC_SOURCES_FILES
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
        src/icouchbase_core_interface.cc
        # modules
)

# list of used becc vendor/thirdparty lib
if(NOT DEFINED BECC_USED_VENDORS_DIR)
    set(BECC_USED_VENDORS_DIR)
endif()

# packages, lib related
## 
## base toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- ${PROJECT_NAME}: using CMAKE_TOOLCHAIN_FILE as `${CMAKE_TOOLCHAIN_FILE}`")
endif()
##
## package manager: vcpkg
set(BECC_USING_VCPKG false)
if(BECC_BUILD_VCPKG)
    set(BECC_VCPKG_DIR)
    set(BECC_VCPKG_TRIPLET)
    set(BECC_VCPKG_INSTALLED_DIR)

    # check VCPKG_DIR env. var.
    if(NOT "$ENV{VCPKG_DIR}" STREQUAL "")
        set(BECC_VCPKG_DIR "$ENV{VCPKG_DIR}")
    endif()

    # check VCPKG_ROOT env. var.
    if(NOT "$ENV{VCPKG_ROOT}" STREQUAL "")
        set(BECC_VCPKG_DIR "$ENV{VCPKG_ROOT}")
    endif()

    if(BECC_BUILD_VCPKG AND BECC_VCPKG_DIR STREQUAL "")
        message(FATAL_ERROR "-- ${PROJECT_NAME}: you are attempting to use vcpkg, but environment variables of `VCPKG_DIR/VCPKG_ROOT` is empty")
    endif()

    # include toolchain
    include("${BECC_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")

    # check vcpkg triplet env. var.
    if(NOT "$ENV{VCPKG_TRIPLET}" STREQUAL "")
        set(BECC_VCPKG_TRIPLET "$ENV{VCPKG_TRIPLET}")
    endif()
    if(NOT "$ENV{VCPKG_DEFAULT_TRIPLET}" STREQUAL "")
        set(BECC_VCPKG_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")
    endif()

    # check vcpkg triplet defined var.
    if(NOT "${VCPKG_TRIPLET}" STREQUAL "")
        set(BECC_VCPKG_TRIPLET "${VCPKG_TRIPLET}")
    endif()
    if(NOT "${VCPKG_DEFAULT_TRIPLET}" STREQUAL "")
        set(BECC_VCPKG_TRIPLET "${VCPKG_DEFAULT_TRIPLET}")
    endif()
    if(NOT "${BECC_BUILD_VCPKG_TRIPLET}" STREQUAL "")
        set(BECC_VCPKG_TRIPLET "${BECC_BUILD_VCPKG_TRIPLET}")
    endif()

    if(BECC_VCPKG_TRIPLET STREQUAL "")
        message(FATAL_ERROR "-- ${PROJECT_NAME}: attempt to use vcpkg but triplet is not defined/set, use `-DVCPKG_TRIPLET=processor_type:system_os_name` or `-DVCPKG_DEFAULT_TRIPLET=processor_type:system_os_name` or set those on your environment variable from -DBECC_BUILD_VCPKG_TRIPLET=processor_type:system_os_name") 
    endif()

    # check and set
    set(BECC_VCPKG_INSTALLED_DIR "${BECC_VCPKG_DIR}/installed/${BECC_VCPKG_TRIPLET}")
    if(EXISTS "${BECC_VCPKG_INSTALLED_DIR}")
        # link bin dirs
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/bin")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/bin")
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/debug/bin")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/debug/bin")

        # include dirs
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/include")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/include")
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/debug/include")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/debug/include")

        # link lib dirs
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/lib")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/lib")
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/debug/lib")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/debug/lib")

        # link share dirs
        include_directories(    "${BECC_VCPKG_INSTALLED_DIR}/share")
        link_directories(BEFORE "${BECC_VCPKG_INSTALLED_DIR}/share")
    else()
        message(FATAL_ERROR "-- ${PROJECT_NAME}: vpckg error")
    endif()

    set(BECC_USING_VCPKG true)
endif()
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
    message(NOTICE "-- ${PROJECT_NAME}: adding jsoncpp since package found")
endif()
##
## openssl
set(BECC_USING_OPENSSL false)

find_package(OpenSSL)
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

if(BECC_USING_VCPKG)
    find_package(unofficial-argon2 CONFIG)

    if(unofficial-argon2_FOUND)
        set(BECC_USING_ARGON2 true)
        message(NOTICE "-- ${PROJECT_NAME}: adding argon2 from vcpkg")
    endif()
else() 
    find_file(BECC_ARGON2_HEADER "argon2.h")
    if(WIN32)
        find_library(BECC_ARGON2_SHARED "argon2.dll")
        find_library(BECC_ARGON2_LIBRARY "argon2.lib")
    else()
        find_library(BECC_ARGON2_SHARED "libargon2.so")
        find_library(BECC_ARGON2_LIBRARY "libargon2.a")
    endif()

    if(BECC_ARGON2_HEADER AND BECC_ARGON2_SHARED AND BECC_ARGON2_LIBRARY)
        set(BECC_USING_ARGON2 true)
        message(NOTICE "-- ${PROJECT_NAME}: adding argon2 since header, shared & lib found")
    else()
        if(NOT BECC_ARGON2_HEADER)
            message(NOTICE "-- ${PROJECT_NAME}: still couldn't found argon2 header")
        endif(NOT BECC_ARGON2_HEADER)

        if(NOT BECC_ARGON2_SHARED)
            message(NOTICE "-- ${PROJECT_NAME}: still couldn't found argon2 shared object/runtime")
        endif(NOT BECC_ARGON2_SHARED)

        if(NOT BECC_ARGON2_LIBRARY)
            message(NOTICE "-- ${PROJECT_NAME}: still couldn't found argon2 library")
        endif(NOT BECC_ARGON2_LIBRARY)
    endif()
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

if(BECC_BUILD_VENDOR_STB)
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

if(BECC_BUILD_VENDOR_SDL3)
    if(BECC_USING_VCPKG)
        find_package(SDL3 CONFIG REQUIRED)
    else()
        set(BECC_VENDOR_SDL3_DIR "${PROJECT_SOURCE_DIR}/vendors/sdl3")

        include_directories(${BECC_VENDOR_SDL3_DIR}/include)

        link_directories(AFTER "${CMAKE_BINARY_DIR}/BECC_SDL3")

        set(SDL_STATIC true)
        set(SDL_TEST_LIBRARY false)

        add_subdirectory(${BECC_VENDOR_SDL3_DIR} BECC_SDL3)
    endif()

    set(BECC_USING_SDL3 true)
    message(NOTICE "-- ${PROJECT_NAME}: adding sdl3")
    list(APPEND BECC_USED_VENDORS_DIR "BECC_SDL3")
endif()
##
## haru
set(BECC_USING_HARU false)

if(BECC_BUILD_VENDOR_HARU)
    if(BECC_USING_VCPKG)
        set(LIBHPDF_SHARED false)
        set(LIBHPDF_STATIC true)
        set(LIBHPDF_EXAMPLES false)

        find_package(unofficial-libharu CONFIG REQUIRED)
    else()
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
    endif()

    set(BECC_USING_HARU true)
    message(NOTICE "-- ${PROJECT_NAME}: adding haru hpdf")
    list(APPEND BECC_USED_VENDORS_DIR "BECC_LIBHARU")
endif()
##
## nanosvg
set(BECC_USING_NANOSVG false)

if(BECC_BUILD_VENDOR_NANOSVG)
    if(BECC_USING_VCPKG)
        find_package(NanoSVG CONFIG REQUIRED)
    else()
        set(BECC_VENDOR_NANOSVG_DIR "${PROJECT_SOURCE_DIR}/vendors/nanosvg")

        if(NOT EXISTS "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")
            file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")
        endif()

        set(BECC_VENDOR_NANOSVG_DIR_NANOSVG)

        file(COPY "${BECC_VENDOR_NANOSVG_DIR}/src/" DESTINATION "${CMAKE_BINARY_DIR}/BECC_NANOSVG/nanosvg")

        set(BECC_VENDOR_NANOSVG_DIR_NANOSVG "${CMAKE_BINARY_DIR}/BECC_NANOSVG")

        include_directories(${BECC_VENDOR_NANOSVG_DIR_NANOSVG})

        add_subdirectory(${BECC_VENDOR_NANOSVG_DIR} BECC_NANOSVG)
    endif()

    set(BECC_USING_NANOSVG true)
    message(NOTICE "-- ${PROJECT_NAME}: adding nanosvg")
    list(APPEND BECC_USED_VENDORS_DIR "BECC_NANOSVG")
endif()
##
## zxing-cpp
set(BECC_USING_ZXING_CPP false)

if(BECC_BUILD_VENDOR_ZXING_CPP)
    set(ZXING_EXPERIMENTAL_API true)
    set(ZXING_EXAMPLES false)
    set(ZXING_BLACKBOX_TESTS false)
    set(ZXING_UNIT_TESTS false)

    if(BECC_USING_VCPKG)
        find_package(ZXing CONFIG REQUIRED)
    else()
        set(BECC_VENDOR_ZXING_CPP_DIR "${PROJECT_SOURCE_DIR}/vendors/zxing-cpp")

        if(NOT EXISTS "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")
            file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")
        endif()

        set(BECC_VENDOR_ZXING_CPP_DIR_ZXING)

        file(COPY "${BECC_VENDOR_ZXING_CPP_DIR}/core/src/" DESTINATION "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP/ZXing")

        set(BECC_VENDOR_ZXING_CPP_DIR_ZXING_DIR "${CMAKE_BINARY_DIR}/BECC_ZXING_CPP")

        include_directories(${BECC_VENDOR_ZXING_CPP_DIR_ZXING_DIR})

        add_subdirectory(${BECC_VENDOR_ZXING_CPP_DIR} BECC_ZXING_CPP)
    endif()

    set(BECC_USING_ZXING_CPP true)
    message(NOTICE "-- ${PROJECT_NAME}: adding zxing-cpp")
    list(APPEND BECC_USED_VENDORS_DIR "BECC_ZXING_CPP")
endif()
##
## couchbase-cxx-client
set(BECC_USING_COUCHBASE_CXX_CLIENT false)

if(BECC_BUILD_VENDOR_COUCHBASE_CXX_CLIENT)
    set(COUCHBASE_CXX_CLIENT_BUILD_TESTS false)
    set(COUCHBASE_CXX_CLIENT_BUILD_DOCS false)
    set(COUCHBASE_CXX_CLIENT_BUILD_EXAMPLES false)
    set(COUCHBASE_CXX_CLIENT_BUILD_TOOLS false)

    if(WIN32)
        add_definitions(-DWIN32)

        set(COUCHBASE_CXX_CLIENT_BUILD_STATIC ON)
    endif(WIN32)

    set(BECC_VENDOR_COUCHBASE_CXX_CLIENT_DIR "${PROJECT_SOURCE_DIR}/vendors/couchbase-cxx-client")

    include_directories("${BECC_VENDOR_COUCHBASE_CXX_CLIENT_DIR}")
    link_directories(AFTER "${BECC_VENDOR_COUCHBASE_CXX_CLIENT_DIR}")

    add_subdirectory(${BECC_VENDOR_COUCHBASE_CXX_CLIENT_DIR} BECC_COUCHBASE_CXX_CLIENT)

    set(BECC_USING_COUCHBASE_CXX_CLIENT true)
    message(NOTICE "-- ${PROJECT_NAME}: adding couchbase-cxx-client")
    list(APPEND BECC_USED_VENDORS_DIR "BECC_COUCHBASE_CXX_CLIENT")

    ## taocpp-json
    include_directories("${CMAKE_BINARY_DIR}/_deps/json-src/include")
    link_directories(AFTER "${CMAKE_BINARY_DIR}/_deps/json-src/include")

    ## taocpp-pegtl
    include_directories("${CMAKE_BINARY_DIR}/_deps/json-src/external/PEGTL/include")
    link_directories(AFTER "${CMAKE_BINARY_DIR}/_deps/json-src/external/PEGTL/include")

    ## spdlog
    include_directories("${CMAKE_BINARY_DIR}/_deps/spdlog-src/include")
    link_directories(AFTER "${CMAKE_BINARY_DIR}/_deps/spdlog-src/include")

    ## msvc need /utf-8
    if(MSVC)
        # check /utf-8
        string(FIND "${CMAKE_CXX_FLAGS}" "/utf-8" POS_UTF8_SLASH)

        if(POS_UTF8_SLASH EQUAL -1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
            message(NOTICE "-- becc: adding /utf-8 flags to msvc")
        endif()
    endif(MSVC)

    # tmp
    if(BECC_IS_DEBUG)
        message(AUTHOR_WARNING "-- ${PROJECT_NAME}: adding [taocpp-json, taocpp-pegtl, spdlog] packages & their dependencies, can make error for this couchbase-cxx-client")
        # maybe force something if BECC_USING_COUCHBASE_CXX_CLIENT, do not add it
    endif()
endif()

# project lib
## object core lib
add_library(${PROJECT_NAME} OBJECT ${BECC_SOURCES_FILES})
## static core lib
add_library(becc_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
## shared code lib
add_library(becc_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
### lib/s name
#### lib output
set(BEGE_OUTPUT_NAME "becc")
#### libs windows and else
if(WIN32)
    set_target_properties(becc_static PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
    set_target_properties(becc_shared PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
else()
    set_target_properties(becc_static PROPERTIES
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
    set_target_properties(becc_shared PROPERTIES
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
endif()

## installed options
### reserved: TODO - install configs

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
        -fPIC
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
        -fPIC
    )
else()
    set(BECC_COMPILER_ID    0)
    set(BECC_COMPILER_GNU   false)
    set(BECC_COMPILER_MSVC  false)
    set(BECC_COMPILER_CLANG false)

    message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
endif()

if(BECC_COMPILER_GNU) # gcc 12.2
    target_link_libraries(${PROJECT_NAME} PRIVATE -lm)

    if(EXISTS "/usr/lib/x86_64-linux-gnu/libm.so")
        target_link_libraries(${PROJECT_NAME} PRIVATE "/usr/lib/x86_64-linux-gnu/libm.so") # somehow build not error
    else()
        message(WARNING "-- ${PROJECT_NAME}: for gcc has error, be warn")
    endif()
endif()

## warning
if(CMAKE_CXX_FLAGS STREQUAL "")
    message(WARNING "-- ${PROJECT_NAME} cxx flags is empty")
endif()

# becc config
configure_file(
    ${PROJECT_SOURCE_DIR}/src/inc/becc/config.in.hh
    ${PROJECT_SOURCE_DIR}/src/inc/becc/config.hh
)

# becc export
generate_export_header(becc
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/inc/becc/export.hh
)
generate_export_header(becc_static
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/inc/becc/export_static.hh
)
generate_export_header(becc_shared
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/inc/becc/export_shared.hh
)

# becc shared definitions
target_compile_definitions(becc_shared PRIVATE BECC_SHARED)

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

# dependencies for static & shared
## loop dependencies target
foreach(BECC_TARGET becc_static becc_shared)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${BECC_TARGET} PRIVATE
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
            -fPIC
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${BECC_TARGET} PRIVATE
            /W4
            /wd4996
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
        target_compile_options(${BECC_TARGET} PRIVATE
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
            -fPIC
        )
    else()
        message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
    endif()

    ## jsoncpp
    if(BECC_USING_JSONCPP)
        if(NOT BECC_BUILD_VCPKG)
            target_link_libraries(${BECC_TARGET} PRIVATE jsoncpp)
        else()
            find_package(jsoncpp CONFIG REQUIRED)
            target_link_libraries(${BECC_TARGET} PRIVATE JsonCpp::JsonCpp)
        endif()
    endif()
    ##
    ## openssl
    if(BECC_USING_OPENSSL)
        target_link_libraries(${BECC_TARGET} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    endif()
    ##
    ## drogon
    if(BECC_USING_DROGON)
        target_link_libraries(${BECC_TARGET} PRIVATE Drogon::Drogon)
    endif()
    ##
    ## argon2
    if(BECC_USING_ARGON2)
        if(BECC_BUILD_VCPKG)
            target_link_libraries(${BECC_TARGET} PRIVATE unofficial::argon2::libargon2)
        else()
            target_link_libraries(${BECC_TARGET} PRIVATE argon2)
        endif()
    endif()
    ##
    ## postgresql
    if(BECC_USING_POSTGRESQL)
        target_link_libraries(${BECC_TARGET} PRIVATE PostgreSQL::PostgreSQL)
    endif()
    ##
    ## scylladb
    if(BECC_USING_SCYLLADB)
        target_link_libraries(${BECC_TARGET} PRIVATE scylla-cpp-driver)
    endif()
    ##
    ## stb
    if(BECC_USING_STB)
        target_include_directories(${BECC_TARGET} PRIVATE ${Stb_INCLUDE_DIR})
    endif()
    ##
    ## sdl
    if(BECC_USING_SDL3)
        if(BECC_BUILD_VCPKG)
            target_link_libraries(${BECC_TARGET} PRIVATE SDL3::SDL3)
        else()
            set_target_properties(SDL3-static PROPERTIES POSITION_INDEPENDENT_CODE ON)
            set_target_properties(SDL_uclibc PROPERTIES POSITION_INDEPENDENT_CODE ON)
            set_target_properties(SDL3_Headers PROPERTIES POSITION_INDEPENDENT_CODE ON)

            target_link_libraries(${BECC_TARGET} PRIVATE SDL3-static SDL_uclibc SDL3_Headers)
        endif()
    endif()
    ##
    ## haru
    if(BECC_USING_HARU)
        if(BECC_BUILD_VCPKG)
            target_link_libraries(${BECC_TARGET} PRIVATE unofficial::libharu::hpdf)
        else()
            set_target_properties(hpdf PROPERTIES POSITION_INDEPENDENT_CODE ON)

            target_link_libraries(${BECC_TARGET} PRIVATE hpdf)

            target_include_directories(${BECC_TARGET} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_SOURCE_OUT})
            target_include_directories(${BECC_TARGET} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_INCLUDE_OUT})
        endif()
    endif()
    ##
    ## nanosvg
    if(BECC_USING_NANOSVG)
        if(BECC_BUILD_VCPKG)
            target_link_libraries(${BECC_TARGET} PRIVATE NanoSVG::nanosvg NanoSVG::nanosvgrast)
        else()
            set_target_properties(nanosvg PROPERTIES POSITION_INDEPENDENT_CODE ON)
            set_target_properties(nanosvgrast PROPERTIES POSITION_INDEPENDENT_CODE ON)

            target_link_libraries(${BECC_TARGET} PRIVATE nanosvg nanosvgrast)
        endif()
    endif()
    ##
    ## zxing-cpp
    if(BECC_USING_ZXING_CPP)
        target_link_libraries(${BECC_TARGET} PRIVATE ZXing::Core ZXing::ZXing)
    endif()
    ##
    ## zxing-cpp
    if(BECC_USING_COUCHBASE_CXX_CLIENT)
        if(WIN32)
            # 
            target_link_libraries(${BECC_TARGET} PRIVATE "${CMAKE_BINARY_DIR}/BECC_COUCHBASE_CXX_CLIENT/asio.lib")

            target_link_libraries(${BECC_TARGET} PRIVATE couchbase_cxx_client_static)
        else()
            target_link_libraries(${BECC_TARGET} PRIVATE couchbase_cxx_client)
        endif()
    endif()
endforeach()

# version shared lib
set_target_properties(becc_shared PROPERTIES
    VERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
    SOVERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
)

# build tests
if(BECC_BUILD_TESTS)
    add_subdirectory(tests BECC_TESTS)
endif(BECC_BUILD_TESTS)

# build tools
if(BECC_BUILD_TOOLS)
    # n/a
endif(BECC_BUILD_TOOLS)

# check if not treat as main project ( treat as sub dir ) as last notice
if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(AUTHOR_WARNING "${PROJECT_NAME}@prothegee: becc CMakeLists.txt is not main/root project")
    message(NOTICE "-- ${PROJECT_NAME}: please add below dir to your project `include_directories` & `link_directories` if you intend to use some becc vendor/thirdparties module:")

    foreach(BECC_VENDOR_DIR IN LISTS BECC_USED_VENDORS_DIR)
        message(NOTICE "-- ${BECC_VENDOR_DIR}, example:
   include_directories(    \"$\{CMAKE_BINARY_DIR}/${BECC_VENDOR_DIR}\")
   link_directories(BEFORE \"$\{CMAKE_BINARY_DIR}/${BECC_VENDOR_DIR}\")
")
    endforeach()
endif()

# check
## cxx flags
if(CMAKE_CXX_FLAGS STREQUAL "")
    message(WARNING "-- ${PROJECT_NAME}: cxx flags is empty for some reason")
else()
    message(NOTICE "-- ${PROJECT_NAME}: build info\n   -DCMAKE_CXX_FLAGS=\"${CMAKE_CXX_FLAGS}\"")
endif()