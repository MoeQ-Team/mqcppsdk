cmake_minimum_required(VERSION 3.0.0)

project(app)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions(-D _WIN_PLATFORM_)
    add_definitions(-D UNICODE)
    endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_definitions(-D _LINUX_PLATFORM_)
    set(CMAKE_CXX_FLAGS "-fvisibility=hidden ${CMAKE_CXX_FLAGS}")
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()

add_definitions(-D X64)

file(GLOB_RECURSE _APP_SOURCE_FILES "src/core/*.cpp" "src/utils/*.cpp")

add_library(app SHARED ${_APP_SOURCE_FILES} "app.cpp")