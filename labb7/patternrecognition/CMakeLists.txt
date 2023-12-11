cmake_minimum_required(VERSION 3.27)

project(patternrecognition)

set(CMAKE_CXX_STANDARD 14)

# Find the QtWidgets and QtGui modules
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

# Set up include directories for Qt headers
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})

add_executable(patternrecognition
        src/fast.cpp
        #src/brute.cpp
        src/Point.cpp
        src/Point.h
)

# Copy text files from res folder to build directory
file(GLOB_RECURSE res_files res/*.txt)
foreach(file ${res_files})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
endforeach()

# Add the Qt Widgets library to the target
target_link_libraries(patternrecognition Qt5::Widgets Qt5::Gui)