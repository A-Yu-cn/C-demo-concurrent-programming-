# # 之前的CMakeLists.txt (创建静态库)
# cmake_minimum_required(VERSION 3.10)

# project(MyLibraryProject VERSION 1.0)

# file(GLOB SRC_FILES "*.cpp")

# # 创建静态库
# add_library(my_static_lib STATIC ${SRC_FILES})

# # 设置库的输出目录
# set_target_properties(my_static_lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 原本在这里进行库的创建，现在打算修改到其他地方去，比如直接放到include下边 