# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# 将源文件添加到变量中
file(GLOB SRC_FILES "*.cpp")

# 创建可执行文件
add_executable(param_trans ${SRC_FILES})

# 将可执行文件链接到公共库
# target_link_libraries(subdir3_executable YourPublicLibraryName)