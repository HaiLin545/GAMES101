cmake_minimum_required(VERSION 3.10)
project(RayTracing)

add_executable(RayTracing main.cpp Object.hpp Vector.hpp Sphere.hpp global.hpp Triangle.hpp Scene.cpp Scene.hpp Light.hpp Renderer.cpp)
#target_compile_options(RayTracing PUBLIC -Wall -Wextra -pedantic -Wshadow -Wreturn-type -fsanitize=undefined)
#target_link_libraries(RayTracing PUBLIC -fsanitize=undefined)
