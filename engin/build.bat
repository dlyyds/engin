@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ==============================
echo 开始构建 GameEngine
echo ==============================

:: 1. 删除 bin 文件夹
if exist bin (
    echo 删除旧的 bin 文件夹...
    rmdir /s /q bin
)

:: 2. CMake 生成
echo CMake 生成工程...
cmake -B bin -G "MinGW Makefiles"

:: 3. 编译
echo 开始编译...
cmake --build bin

:: 4. 复制文件到上层 sandbox（正确路径）
echo 复制文件到 sandbox...
copy /y "bin\libGameEngine.dll" "..\sandbox\"
copy /y "bin\libGameEngine.dll.a" "..\sandbox\"

echo.
echo ==============================
echo 构建完成！
echo ==============================
pause