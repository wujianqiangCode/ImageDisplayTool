cmake_minimum_required(VERSION 3.10)

option(ENABLE_UIC_MOC "enbale auto_mic auto_moc" ON)

if(ENABLE_MIC_MOC)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTUIC ON)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<IF:$<CONFIG:Release>,Release,Debug>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

project(ImageDisplayTool CXX)

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/Qt5.12.12/5.12.12/msvc2017_64/lib/cmake")

    if(MSVC)
        add_compile_options(/wd4244)
    endif()
else()
endif()

find_package(Qt5 COMPONENTS core gui widgets REQUIRED)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/ImageDisplayTool IMAGEDISPLAY_SOURCES)
add_library(ImageDisplayTool SHARED ${IMAGEDISPLAY_SOURCES})
target_include_directories(ImageDisplayTool PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ImageDisplayTool)
target_compile_definitions(ImageDisplayTool PUBLIC WIN32 _DEBUG)

file(GLOB QTRENDERTOOL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/QtRenderTool/QtRenderTool/*.cpp")
file(GLOB QTRENDERTOOL_HEADERS "${CMAKE_CURRENT_LIST_DIR}/QtRenderTool/QtRenderTool/*.h")
file(GLOB QTRENDERTOOL_UIS "${CMAKE_CURRENT_LIST_DIR}/QtRenderTool/QtRenderTool/*.ui")

add_executable(QtRenderTool WIN32 ${QTRENDERTOOL_SOURCES} ${QTRENDERTOOL_HEADERS} ${QTRENDERTOOL_UIS})
target_link_libraries(QtRenderTool PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui)
set_target_properties(QtRenderTool PROPERTIES AUTOMOC ON AUTOUIC ON)

# intellisense
target_include_directories(QtRenderTool PUBLIC
    ${CMAKE_BINARY_DIR}/QtRenderTool_autogen/include_${CMAKE_BUILD_TYPE}
    ${CMAKE_BINARY_DIR}/QtRenderTool_autogen/include)