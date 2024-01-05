cmake_minimum_required(VERSION 3.27)
project(trailblazer)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib/StanfordCPPLib)
include_directories(lib/StanfordCPPLib/private)
include_directories(src)

file(GLOB LIB_SOURCES lib/StanfordCPPLib/*.cpp lib/StanfordCPPLib/*.h lib/StanfordCPPLib/private/*.h)

file(GLOB SRC_SOURCES src/*.cpp src/*.h)

add_executable(trailblazer ${LIB_SOURCES} ${SRC_SOURCES})

# Copy resources to build directory
file(GLOB_RECURSE res_files res/*.txt)
foreach(file ${res_files})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
endforeach()