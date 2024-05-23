cmake_minimum_required(VERSION 3.23.3)
project(Rasterizer)


set(CMAKE_CXX_STANDARD 17)

# os不同，opencv产物中cmake配置的路径不同
message(STATUS "Running OS: " ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../lib/opencv)
else()
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../lib/opencv/lib/cmake/opencv4)
endif()

# opencv
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV found in: " ${OpenCV_INCLUDE_DIRS})
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

#eigen3
set(Eigen3_DIR ${CMAKE_SOURCE_DIR}/../lib/eigen3/share/eigen3/cmake)
find_package(Eigen3 REQUIRED)
if(EIGEN3_FOUND)
    message(STATUS "Eigen3 found in: " ${EIGEN3_INCLUDE_DIRS})
    include_directories(${EIGEN3_INCLUDE_DIRS})
endif()

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})
