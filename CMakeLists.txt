cmake_minimum_required(VERSION 3.23.3)

set(CMAKE_CXX_STANDARD 17)

# 使用vcpkg安装好的依赖
set(VCPKG_ROOT D:/envs/vcpkg)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

project(GAMES101)

find_package(Eigen3 REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(./work0)
add_subdirectory(./Assignment1)
add_subdirectory(./Assignment2)
add_subdirectory(./Assignment3)
add_subdirectory(./Assignment4)

