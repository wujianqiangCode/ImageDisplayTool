#指定cmake的最小版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#指定项目名称
PROJECT(TestDemo LANGUAGES CXX)

# add OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
 
# Add OpenGL headers location to your include paths
include_directories(${OPENGL_INCLUDE_DIR})

#将所有文件编译成EXE
ADD_EXECUTABLE(TestDemo main.cpp)

#加载静态LIB
if (WIN32)
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${PROJECT_SOURCE_DIR}/../Install/Win/x64/Release/ImageDisplayTool.lib 
    ${OPENGL_LIBRARIES})
elseif (APPLE)
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${PROJECT_SOURCE_DIR}/../Install/Mac/x64/Release/libImageDisplayTool.a 
    ${OPENGL_LIBRARIES})
elseif (UNIX)
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${PROJECT_SOURCE_DIR}/../Install/Linux/x64/Release/libImageDisplayTool.a 
    ${OPENGL_LIBRARIES})
endif ()

#设置exe文件生成路径
if (WIN32)
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Install/Win/x64/Release)   
elseif (APPLE)
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Install/Mac/x64/Release)   
elseif (UNIX)
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Install/Linux/x64/Release)   
endif ()