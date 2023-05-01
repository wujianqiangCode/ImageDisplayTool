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
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${OPENGL_LIBRARIES} 
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/ImageDisplayTool.lib)
elseif (APPLE)
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${OPENGL_LIBRARIES} 
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/libImageDisplayTool.a)
elseif (UNIX)
    TARGET_LINK_LIBRARIES(TestDemo PRIVATE  ${OPENGL_LIBRARIES} 
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/libImageDisplayTool.a)    
endif ()