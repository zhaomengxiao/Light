# 工程名
set (PROJECT_NAME Light)

PROJECT(${PROJECT_NAME})

message("工程名: " ${PROJECT_NAME})

message("工程目录: " ${PROJECT_SOURCE_DIR}) 

# 最低版本需求
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH 
    "D:/Software/qt/5.13.1/msvc2015_64"
    "E:/cpplib/dlib-19.18/install"
#    "E:/cpplib/googletest-1.10.x/install"
    ) 

SET(CMAKE_BUILD_TYPE "DEBUG")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set (INSTALL_RPATH ${PROJECT_BINARY_DIR}/install)

message("编译后可执行程序目录: " ${EXECUTABLE_OUTPUT_PATH})

message("编译后库程序文件目录: " ${LIBRARY_OUTPUT_PATH})

#添加.h文件
SET(LIGHT_HEADER_FILES
	svpng.inc
    macrodef.h
	SDF.h
	Scene.h
    lightwindow.h
    rasterWindow/rasterwindow.h
)

#添加.cpp文件
SET(LIGHT_SOURCE_FILES
    SDF.cpp
	Scene.cpp
    lightwindow.cpp
    rasterWindow/rasterwindow.cpp
    main.cpp
)


#添加QT
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
SET(QT_LIB
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    )

SET(QT_BIN ${_qt5_root_dir}/../../bin)
message("QT_dll目录：" ${QT_BIN} )
set(QT_DLL 
    ${QT_BIN}/Qt5Cored.dll
    ${QT_BIN}/Qt5Guid.dll
    ${QT_BIN}/Qt5Widgetsd.dll
    )

#添加dlib
find_package(dlib REQUIRED)

add_executable(light ${LIGHT_HEADER_FILES} ${LIGHT_SOURCE_FILES})

target_link_libraries(light ${QT_LIB} dlib::dlib)

install (TARGETS light DESTINATION ${INSTALL_RPATH})
install(FILES ${QT_DLL} DESTINATION ${INSTALL_RPATH})

