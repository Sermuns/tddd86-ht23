cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 11)

# Add your source files
set(SOURCES
        Event.cpp
        Fish.cpp
        main.cpp
        Simulation.cpp
)

# Find and include necessary packages if needed

# Add the executable
add_executable(app ${SOURCES})

# Include headers
file(GLOB HEADERS *.h)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})