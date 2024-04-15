# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# 将源文件添加到变量中
file(GLOB SRC_FILES "*.cpp")

# 添加库文件的搜索路径
# link_directories(${CMAKE_BINARY_DIR}/lib/Debug)
# 创建可执行文件
add_executable(mutex_protect ${SRC_FILES})

# 将可执行文件链接到公共库
# target_link_libraries(mutex_protect PRIVATE my_static_lib)