cmake_minimum_required(VERSION 3.23.3)
project(Rasterizer2)

add_executable(Rasterizer2 main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})