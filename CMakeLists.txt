cmake_minimum_required(VERSION 3.0.0)

project(mqcppsdk)

set(CMAKE_CXX_STANDARD 20)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions(-D _WIN_PLATFORM_)
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_definitions(-D _LINUX_PLATFORM_)
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()

if ("${DCMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()

add_definitions(-D X64)

file(GLOB_RECURSE _MQCPPSDK_SOURCE_FILES "src/core/*.cpp" "src/utils/*.cpp")

add_library(mqcppsdk ${_MQCPPSDK_SOURCE_FILES})