#!/bin/bash

# Find the project file (*.pro) in the current directory
PROJECT_FILE=$(find . -maxdepth 1 -type f -name "*.pro" -print -quit)

# Check if a project file was found
if [ -z "$PROJECT_FILE" ]; then
    echo "No Qt project file (*.pro) found in the current directory."
    exit 1
fi

# Extract the project name from the project file
PROJECT_NAME=$(basename "$PROJECT_FILE" .pro)

# Specify the build directory name
BUILD_DIR="build-${PROJECT_NAME}"

# Check if the build directory exists, and if not, create it
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Change to the build directory
cd "$BUILD_DIR"

# Run qmake to generate Makefiles (suppressing output)
qmake "../${PROJECT_NAME}.pro" -r

# Build the project using make (suppressing output)
make -s -j$(nproc) 

# Check if the build was successful
if [ $? -eq 0 ]; then
    ./"${PROJECT_NAME}"
else
    echo "Build failed."
fi
