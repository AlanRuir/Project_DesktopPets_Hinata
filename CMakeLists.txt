cmake_minimum_required(VERSION 3.5)

project(Hinata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Qml Quick Multimedia Widgets REQUIRED)

add_executable(Hinata 
    src/main.cpp
    src/hinata.cpp
    include/hinata.h
    qrc/main.qrc)

target_include_directories(Hinata PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Hinata PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::Multimedia Qt5::Widgets)