# 获取src目录下的所有子文件夹
file(GLOB children *)

# 遍历子文件夹
foreach(child ${children})
  if(IS_DIRECTORY ${child})
    # 添加子文件夹
    add_subdirectory(${child})
  endif()
endforeach()