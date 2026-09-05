cmake_minimum_required(VERSION 3.16)
project(MLCS VERSION 2.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets Network Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets Network Multimedia MultimediaWidgets)

set(SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    azimuthwidget.h
    azimuthwidget.cpp
    elevationwidget.h
    elevationwidget.cpp
    missilewidget.h
    missilewidget.cpp
    targetwidget.h
    targetwidget.cpp
    TransparentPushButton.h
    TransparentPushButton.cpp
    screenrecorder.h
    screenrecorder.cpp
)

add_executable(MLCS ${SOURCES}
    Resources.qrc
    transparentpushbutton.h transparentpushbutton.cpp
    screenrecorder.h screenrecorder.cpp
)

target_link_libraries(MLCS PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

target_include_directories(MLCS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
