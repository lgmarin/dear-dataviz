cmake_minimum_required(VERSION 3.22)
project(DearDataViz VERSION 1.0)

# Set the C++ standard to 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
# Find the SDL2 package. The dev container has this installed.
find_package(SDL2 REQUIRED)
add_subdirectory(libs/catch2)

# --- Source Code ---
add_subdirectory(src)

# --- Main Executable ---
# Create the final application executable from the root main.cpp.
add_executable(dear_dataviz src/main.cpp)

# Link the executable against our application logic library.
# This will transitively link dataviz_ui and all its dependencies.
target_link_libraries(dear_dataviz PRIVATE dataviz_app)

# --- Testing ---
# Enable testing and add the 'test' directory (singular).
enable_testing()
add_subdirectory(test)