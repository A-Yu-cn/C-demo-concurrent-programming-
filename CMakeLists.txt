cmake_minimum_required(VERSION 3.8)
project(Concurrent_Programming_Learning)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加include目录
include_directories(include)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# 添加子目录（src）
add_subdirectory(src)