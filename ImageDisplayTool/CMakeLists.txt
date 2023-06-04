# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (ImageDisplayTool)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)


# 设置静态库生成路径
if (WIN32)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Install/Win/x64/Release)
elseif (APPLE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Install/Mac/x64/Release)
elseif (UNIX)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Install/Linux/x64/Release) 
endif ()

# 生成链接库
add_library(ImageDisplayTool ${DIR_SRCS})



