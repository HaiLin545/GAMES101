# Platform: windows

cmake_minimum_required (VERSION 3.23.3)
project (Transformation)

# eigen3
set(Eigen3_DIR ${CMAKE_SOURCE_DIR}/../lib/Eigen3/share/eigen3/cmake)
find_package(Eigen3 REQUIRED)
if(EIGEN3_FOUND)
    message(STATUS "Eigen3 found in: " ${EIGEN3_INCLUDE_DIRS})
    include_directories(${EIGEN3_INCLUDE_DIRS})
endif()

add_executable (Transformation main.cpp)
