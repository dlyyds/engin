# CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(sandbox)

# ====================== C++17 ======================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ====================== 输出目录 ======================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)


# ====================== 中间文件目录 ======================
# 编译临时文件全部放 bin/int
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# ====================== 自动加载所有 cpp/h 文件 ======================
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/*.h
)

add_executable(${PROJECT_NAME} SandboxApp.cpp)

target_include_directories(
    ${PROJECT_NAME}                # 你的目标名字
    PRIVATE              # 固定写这个
    ${CMAKE_SOURCE_DIR}/../engin/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libGameEngine.dll.a)



