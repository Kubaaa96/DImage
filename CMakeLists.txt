cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

project(DImage LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(OpenCV_DIR "D:\\OpenCV\\opencv\\build\\")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    # Headers
    src/app/openCVOperations.h

    src/gui/mainwindow.h
    src/gui/imageviewer.h
    src/gui/imagecontainer.h
    src/gui/informationaboutimage.h
    src/gui/aboutwidget.h
    src/gui/optionwidget.h
    src/gui/edgedetectionwidget.h
    src/gui/abstractoperationwidget.h
    
    # Sources
    src/app/main.cpp
    src/app/openCVOperations.cpp

    src/gui/mainwindow.cpp
    src/gui/imageviewer.cpp
    src/gui/imagecontainer.cpp
    src/gui/informationaboutimage.cpp
    src/gui/aboutwidget.cpp
    src/gui/optionwidget.cpp
    src/gui/edgedetectionwidget.cpp
    src/gui/abstractoperationwidget.cpp

    # Forms
    src/gui/mainwindow.ui
    src/gui/informationaboutimage.ui
    src/gui/aboutwidget.ui
    src/gui/optionwidget.ui
    src/gui/edgedetectionwidget.ui

    # Resources
    src/icons/icons.qrc
    )

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${OpenCV_LIBS})
