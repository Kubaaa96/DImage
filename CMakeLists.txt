cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(DImage LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    # Headers
    src/gui/mainwindow.h
    src/gui/imageviewer.h
    
    # Sources
    src/app/main.cpp
    src/gui/mainwindow.cpp
    src/gui/imageviewer.cpp

    # Forms
    src/gui/mainwindow.ui
    )

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)
