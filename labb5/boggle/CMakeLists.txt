cmake_minimum_required(VERSION 3.26)
project(boggle)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(lib/StanfordCPPLib)
include_directories(lib/StanfordCPPLib/private)
include_directories(res)
include_directories(src)

# Include QT
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Globbing for source files, headers and resources
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "lib/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h" "lib/*.h")
#file(GLOB_RECURSE RESOURCE_FILES "res/*.dat")

# Add the executable
add_executable(boggle ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

# Link Qt5 Widgets library
target_link_libraries(boggle Qt5::Widgets)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/EnglishWords.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)