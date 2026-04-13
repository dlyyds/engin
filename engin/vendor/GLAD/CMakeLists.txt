# glad/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(glad)


# 编译 glad.c
add_library(glad STATIC src/glad.c)

target_include_directories(glad
    PUBLIC  # 公开给外部使用
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)