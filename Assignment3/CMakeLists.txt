cmake_minimum_required(VERSION 3.23.3)
project(Rasterizer3)

add_compile_definitions(MODEL_PATH="${CMAKE_CURRENT_SOURCE_DIR}/models/")

add_executable(Rasterizer3 main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp Texture.hpp Texture.cpp Shader.hpp OBJ_Loader.h)
target_link_libraries(Rasterizer3 ${OpenCV_LIBRARIES})
#target_compile_options(Rasterizer PUBLIC -Wall -Wextra -pedantic)