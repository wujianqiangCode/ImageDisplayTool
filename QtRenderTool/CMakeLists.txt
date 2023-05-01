#指定cmake的最小版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#指定项目名称
PROJECT(QtRenderTool LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)


add_executable(QtRenderTool
    Socket.cpp
    QtRenderTool.ui
    QtRenderTool.cpp
    main.cpp
)

#加载静态LIB
if (WIN32)
    TARGET_LINK_LIBRARIES(QtRenderTool PRIVATE  Qt5::Widgets Qt5::Core Qt5::Gui 
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/ImageDisplayTool.lib)
elseif (APPLE)
    TARGET_LINK_LIBRARIES(QtRenderTool PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/libImageDisplayTool.a)
elseif (UNIX)
    TARGET_LINK_LIBRARIES(QtRenderTool PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui
    ${PROJECT_SOURCE_DIR}/../ImageDisplayTool/libImageDisplayTool.a)    
endif ()