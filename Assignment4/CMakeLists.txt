cmake_minimum_required(VERSION 3.10)
project(BezierCurve)

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve ${OpenCV_LIBRARIES})
