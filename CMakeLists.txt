cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME_STR tracker-c)
PROJECT(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

# flags
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")



file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Compile
add_library(tracker-c STATIC ${SRC_FILES} ${HEADER_FILES})
