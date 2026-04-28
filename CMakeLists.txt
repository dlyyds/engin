cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
# 总项目名称
project(GE)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 中间文件目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin-int)


set(GE_NAME GE)       # 引擎DLL名称
set(APP_NAME Sandbox)  

#GameGEe DLL

add_subdirectory(GE/vendor/spdlog)
add_subdirectory(GE/vendor/glfw)
add_subdirectory(GE/vendor/glad)
add_subdirectory(GE/vendor/imgui)

file(GLOB GE_SRC
    ${CMAKE_SOURCE_DIR}/GE/src/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/src/Platform/Windows/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/src/Platform/OpenGL/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/src/ImGui/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/src/Renderer/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/src/Core/*.cpp
    ${CMAKE_SOURCE_DIR}/GE/vendor/stbimage/*.cpp
)


add_library(${GE_NAME} STATIC ${GE_SRC})
target_include_directories(${GE_NAME} PUBLIC 
${CMAKE_SOURCE_DIR}/GE/include/GE
${CMAKE_SOURCE_DIR}/GE/vendor/glm
${CMAKE_SOURCE_DIR}/GE/vendor/stbimage
)
target_compile_definitions(${GE_NAME} PRIVATE 
GLFW_INCLUDE_NONE
GE_DEBUG
NOMINMAX
)
target_link_libraries(${GE_NAME} PUBLIC spdlog::spdlog glfw glad imgui )


if(WIN32)
    target_link_libraries(${GE_NAME} PUBLIC
        opengl32        # OpenGL 
    )
endif()
# 开启预编译头 PCH
target_precompile_headers(${GE_NAME} PRIVATE GE/include/GE/pch.h)


#Sandbox EXE 调用 DLL
# ==============================================

file(GLOB APP_SRC
   ${CMAKE_SOURCE_DIR}/sandbox/*.cpp
)


add_executable(${APP_NAME} ${APP_SRC})
target_include_directories(${APP_NAME} PRIVATE 
${CMAKE_SOURCE_DIR}/GE/include
${CMAKE_SOURCE_DIR}/GE/vendor/glm
${CMAKE_SOURCE_DIR}/GE/vendor/imgui
)
target_link_libraries(${APP_NAME} PRIVATE ${GE_NAME})
