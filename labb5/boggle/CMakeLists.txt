cmake_minimum_required(VERSION 3.10)

project(Boggle)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add warning flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wreturn-type)
endif()

# Define the source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/lib/StanfordCPPLib/*.cpp")

# Define the header files
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/lib/StanfordCPPLib/*.h")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/StanfordCPPLib")

# Define the files to copy
set(FILES_TO_COPY "${CMAKE_SOURCE_DIR}/res/*" "${CMAKE_SOURCE_DIR}/lib/*.jar")

# Define the destination directory
set(DEST_DIR "${CMAKE_BINARY_DIR}")

# Copy files
foreach(FILE IN ${FILES_TO_COPY})
    file(COPY ${FILE} DESTINATION ${DEST_DIR})
endforeach()

# Add custom target to ensure files are copied every time
add_custom_target(copyResources ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${DEST_DIR}/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/lib ${DEST_DIR}/lib
    COMMENT "Copying resources to build directory"
)