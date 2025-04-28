cmake_minimum_required(VERSION 3.15)

# package
set(BECC_VERSION_MAJOR 0)
set(BECC_VERSION_MINOR 6)
set(BECC_VERSION_PATCH 0)
set(BECC_VERSION_RELEASE_DATE 20250428)

# package project
project(becc
    VERSION "${BECC_VERSION_MAJOR}.${BECC_VERSION_MINOR}.${BECC_VERSION_PATCH}"
    LANGUAGES CXX C
)

# option/s
## build tests, default false/OFF
option(BUILD_TESTS              "build project test/s" OFF)
## build tools, default false/OFF
option(BUILD_TOOLS              "build project tool/s" OFF)
## build use vcpkg
option(BUILD_USE_VCPKG          "build using vcpkg, will look environment variable of VCPKG_DIR/VCPKG_ROOT & VCPKG_DEFAULT_TRIPLET/DEFAULT_TRIPLET" OFF)
## build using custom output dir
option(BUILD_CUSTOM_OUTPUT      "build using custom output if not empty" "")
if(NOT BUILD_CUSTOM_OUTPUT STREQUAL "")
set(EXECUTABLE_OUTPUT_PATH         "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}")

message(NOTICE "-- ${PROJECT_NAME} using build custom output as "${CMAKE_CURRENT_SOURCE_DIR}/${BUILD_CUSTOM_OUTPUT}"")
endif()
## build vendor sdl
option(BUILD_VENDOR_SDL         "build vendor sdl" OFF)
## build vendor stb
option(BUILD_VENDOR_STB         "build vendor stb" OFF)
## build vendor haru
option(BUILD_VENDOR_HARU        "build vendor haru" OFF)
## build vendor nanosvg
option(BUILD_VENDOR_NANOSVG     "build vendor nanosvg" OFF)
## build vendor zxing-cpp
option(BUILD_VENDOR_ZXING_CPP   "build vendor zxing-cpp" OFF)

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

## cxx standard
### by default build is set for gnu linux environment
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)

    if(MSVC)
        list(APPEND CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
else()
    if(MSVC)
        list(APPEND CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
endif()

## reserved: system, processor, build, processor

# include base
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# check deps
## openssl
find_dependency(Drogon)
find_dependency(OpenSSL)
find_dependency(PostgreSQL)

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
    src/inc/becc/functions/cryptography.hh
    src/inc/becc/functions/date_and_time.hh
    src/inc/becc/functions/generate.hh
    src/inc/becc/functions/system.hh
    src/inc/becc/functions/utility.hh
)
list(APPEND BEC_HEADERS_FILES ${BEC_HEADERS_FILES_FUNCTIONS})
## interfaces
## modules

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
        src/cryptography.cc
        src/date_and_time.cc
        src/generate.cc
        src/system.cc
        src/utility.cc
        # interfaces
        # modules
)

# packages, lib related
## 
## base toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- ${PROJECT_NAME}: using CMAKE_TOOLCHAIN_FILE as `${CMAKE_TOOLCHAIN_FILE}`")
endif()
## base vcpkg
set(BECC_USING_VCPKG false)
if(BUILD_USE_VCPKG)
    set(BECC_VCPKG_DIR "")
    set(BECC_VCPKG_TRIPLET "")
    set(BECC_VCPKG_INSTALLED_DIR "")

    # check VCPKG_DIR env. var.
    if(NOT "$ENV{VCPKG_DIR}" STREQUAL "")
        set(BECC_VCPKG_DIR "$ENV{VCPKG_DIR}")
    endif()

    # check VCPKG_ROOT env. var.
    if(NOT "$ENV{VCPKG_ROOT}" STREQUAL "")
        set(BECC_VCPKG_DIR "$ENV{VCPKG_ROOT}")
    endif()

    if(BUILD_USE_VCPKG AND BECC_VCPKG_DIR STREQUAL "")
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

    if(BECC_VCPKG_TRIPLET STREQUAL "")
       message(FATAL_ERROR "-- ${PROJECT_NAME}: attempt to use vcpkg but triplet is not defined/set, use `-DVCPKG_TRIPLET=processor_type-system_os_name` or `-DVCPKG_DEFAULT_TRIPLET=processor_type-system_os_name` or set those on your environment variable") 
    endif()

    # check and set
    set(BECC_VCPKG_INSTALLED_DIR "${BECC_VCPKG_DIR}/installed/${BECC_VCPKG_TRIPLET}")
    if(EXISTS "${BECC_VCPKG_INSTALLED_DIR}")
        # include dirs
        include_directories("${BECC_VCPKG_INSTALLED_DIR}/include")
        include_directories("${BECC_VCPKG_INSTALLED_DIR}/debug/include")

        # link bin dirs
        link_directories("${BECC_VCPKG_INSTALLED_DIR}/bin")
        link_directories("${BECC_VCPKG_INSTALLED_DIR}/debug/bin")

        # link lib dirs
        link_directories("${BECC_VCPKG_INSTALLED_DIR}/lib")
        link_directories("${BECC_VCPKG_INSTALLED_DIR}/debug/lib")

        set(BECC_USING_VCPKG true)
    else()
        message(FATAL_ERROR "-- ${PROJECT_NAME}: vpckg error")
    endif()
endif()
## curl
set(CURL_FOUND)
set(BECC_USING_CURL false)
set(BECC_USING_CURL_EXECUTEABLE false)

find_package(CURL)

if(CURL_FOUND)
    set(BECC_USING_CURL true)
    message(NOTICE "-- ${PROJECT_NAME}: lib curl found")
else()
    message(NOTICE "-- ${PROJECT_NAME}: lib curl not found")
endif()

if(WIN32)
    find_file(BECC_CURL_EXECUTEABLE "curl.exe")
else()
    find_file(BECC_CURL_EXECUTEABLE "curl")
endif()

if(BECC_CURL_EXECUTEABLE)
    set(BECC_USING_CURL_EXECUTEABLE true)
    message(NOTICE "-- ${PROJECT_NAME}: curl executeable found ${BECC_CURL_EXECUTEABLE}")
else()
    message(NOTICE "-- ${PROJECT_NAME}: curl executeable not found")
endif()
## openssl
set(OpenSSL_FOUND)
set(BECC_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(BECC_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}: lib openssl found")
else()
    message(NOTICE "-- ${PROJECT_NAME}: lib openssl not found, attempt to find headers")
    find_file(BEC_OPENSSL_DIR "openssl/evp.h")
    if(BEC_OPENSSL_DIR)
        get_filename_component(OpenSSL_DIR "${BEC_OPENSSL_DIR}" DIRECTORY)

        set(BECC_USING_OPENSSL true)
        # include_directories(${OpenSSL_DIR})

        message(NOTICE "-- ${PROJECT_NAME}: openssl header found in ${BEC_OPENSSL_DIR}")
    else()
        message(NOTICE "-- ${PROJECT_NAME}: openssl header not found")
    endif()
endif()
## jsoncpp
set(jsoncpp_FOUND)
set(BECC_USING_JSONCPP false)

find_package(jsoncpp CONFIG)

if(jsoncpp_FOUND)
    set(BECC_USING_JSONCPP true)
    message(NOTICE "-- ${PROJECT_NAME}: jsoncpp package found")
else()
    set(BECC_VENDOR_JSONCPP_DIR ${PROJECT_SOURCE_DIR}/vendors/jsoncpp)

    set(JSONCPP_WITH_TESTS false)
    set(JSONCPP_WITH_EXAMPLE false)
    set(JSONCPP_WITH_CMAKE_PACKAGE true)

    add_subdirectory(${BECC_VENDOR_JSONCPP_DIR} BECC_JSONCPP)

    set(BECC_USING_JSONCPP true)

    message(NOTICE "-- ${PROJECT_NAME}: jsoncpp using internal vendor dir")
endif()
## argon2
set(BECC_USING_ARGON2 false)

find_file(BECC_ARGON2_INCLUDE_DIRS "argon2.h")
if(BECC_ARGON2_INCLUDE_DIRS)
    set(BECC_USING_ARGON2 true)
    message(NOTICE "-- ${PROJECT_NAME}: argon2 header found")
endif()
## drogon
set(Drogon_FOUND)
set(BECC_USING_DROGON false)

find_package(Drogon CONFIG)
if(Drogon_FOUND)
    set(BECC_USING_DROGON true)
    message(NOTICE "-- ${PROJECT_NAME}: drogon package found")
endif()
## postgresql
set(PostgreSQL_FOUND)
set(BECC_USING_POSTGRESQL false)

find_package(PostgreSQL)
if(PostgreSQL_FOUND)
    set(BECC_USING_POSTGRESQL true)
    message(NOTICE "-- ${PROJECT_NAME}: postgresql package found")
endif()
## scylladb / linux only
set(BECC_USING_SCYLLADB false)

if(LINUX)
    find_file(BECC_SCYLLA_EXECUTEABLE "scylla")
    find_file(BECC_CASSANDRA_HEADER "cassandra.h")

    if(BECC_SCYLLA_EXECUTEABLE AND BECC_CASSANDRA_HEADER)
        set(BECC_USING_SCYLLADB true)
        message(NOTICE "-- ${PROJECT_NAME}: scylladb dependencies seems found")
    endif()
endif()
## sdl
set(BECC_USING_SDL false)
if(BUILD_VENDOR_SDL)
    set(BECC_VENDOR_SDL_DIR "${PROJECT_SOURCE_DIR}/vendors/sdl")

    include_directories(${BECC_VENDOR_SDL_DIR}/include)

    link_directories(AFTER "${CMAKE_BINARY_DIR}/BECC_SDL")

    set(SDL_STATIC true)
    set(SDL_TEST_LIBRARY false)

    add_subdirectory(${BECC_VENDOR_SDL_DIR} BECC_SDL)

    set(BECC_USING_SDL true)
    message(NOTICE "-- ${PROJECT_NAME}: sdl build using vendor")
endif()
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
    message(NOTICE "-- ${PROJECT_NAME}: stb build using vendor")
endif()
## haru
set(BECC_USING_HARU false)
if(BUILD_VENDOR_HARU)
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
    message(NOTICE "-- ${PROJECT_NAME}: haru build using vendor")
endif()
## nanosvg
set(BECC_USING_NANOSVG false)
if(NOT BUILD_SKIPPED_VENDOR_NANOSVG)
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
    message(NOTICE "-- ${PROJECT_NAME}: nanosvg build using vendor")
endif()
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
    message(NOTICE "-- ${PROJECT_NAME}: zxing-cpp build using vendor")
endif()

# project lib
add_library(${PROJECT_NAME} ${BEC_SOURCES_FILES})

# target libs
## openssl
if(BECC_USING_OPENSSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()
## jsoncpp
if(BECC_USING_JSONCPP)
    if(jsoncpp_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp)
    endif()
endif()
## argon2
if(BECC_USING_ARGON2)
    target_link_libraries(${PROJECT_NAME} PRIVATE argon2)
endif()
# postgresql
if(BECC_USING_POSTGRESQL)
    if(PostgreSQL_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
    endif()
endif()
## scylladb
if(BECC_USING_SCYLLADB)
    target_link_libraries(${PROJECT_NAME} PRIVATE scylla-cpp-driver)
endif()
## sdl
if(BECC_USING_SDL)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-static SDL_uclibc SDL3_Headers)
endif()
## stb
if(BECC_USING_STB)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
endif()
## haru
if(BECC_USING_HARU)
    target_link_libraries(${PROJECT_NAME} PRIVATE hpdf)

    target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_INCLUDE})
    target_include_directories(${PROJECT_NAME} PRIVATE ${BECC_VENDOR_LIBHARU_DIR_INCLUDE_OUT})
endif()
## zxing-cpp
if(BECC_USING_ZXING_CPP)
    target_link_libraries(${PROJECT_NAME} PRIVATE ZXing::Core ZXing::ZXing)
endif()
## nanosvg
if(BECC_USING_NANOSVG)
    target_link_libraries(${PROJECT_NAME} PRIVATE nanosvg nanosvgrast)
endif()

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