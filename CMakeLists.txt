cmake_minimum_required(VERSION 3.10)


# 总项目名称
project(GameEngine)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 中间文件目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin-int)


set(ENGINE_NAME GameEngine)       # 引擎DLL名称
set(APP_NAME Sandbox)  

#GameEngine DLL
add_subdirectory(engin/vendor/spdlog)

file(GLOB ENGINE_SRC
    ${CMAKE_SOURCE_DIR}/engin/src/*.cpp
    ${CMAKE_SOURCE_DIR}/engin/include/**/*.h

)


add_library(${ENGINE_NAME} SHARED ${ENGINE_SRC})
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engin/include/GE)
target_compile_definitions(${ENGINE_NAME} PRIVATE GAME_ENGINE_BUILD)
target_link_libraries(${ENGINE_NAME} PUBLIC spdlog::spdlog)

# 开启预编译头 PCH
target_precompile_headers(${ENGINE_NAME} PRIVATE engin/include/GE/pch.h)

#Sandbox EXE 调用 DLL
# ==============================================
add_executable(${APP_NAME} ${CMAKE_SOURCE_DIR}/sandbox/SandboxApp.cpp)
target_include_directories(${APP_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engin/include)
target_link_libraries(${APP_NAME} PRIVATE ${ENGINE_NAME})