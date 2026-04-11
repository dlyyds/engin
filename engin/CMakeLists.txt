# CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(GameEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# ====================== C++17 ======================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ====================== 输出目录 ======================
# DLL / EXE 最终放在 bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ====================== 中间文件目录 ======================
# 编译临时文件全部放 bin/int
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin/int)



# ====================== 自动加载所有 cpp/h 文件 ======================
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/include/*.h
)

# ====================== 编译成 DLL（核心） ======================

add_subdirectory(vendor/spdlog)


add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_ENGINE_BUILD)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
)


