cmake_minimum_required(VERSION 3.22)
project(DearDataViz VERSION 1.0)

# Set the C++ standard to 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
# Find the SDL2 package. The dev container has this installed.
find_package(SDL2 REQUIRED)

# Add Catch2 as a subdirectory. This is correct as Catch2 is CMake-friendly.
add_subdirectory(libs/catch2)

# --- Source Code ---
# Add the source directory for our main application.
# NOTE: We do NOT add imgui here. It will be handled inside src/CMakeLists.txt
add_subdirectory(src)

# --- Testing ---
# Enable testing and add the 'test' directory (singular).
enable_testing()
add_subdirectory(test)