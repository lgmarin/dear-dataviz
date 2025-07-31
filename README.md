# Data Visualization Tool

## _Data Acquisition and Visualization Software written in C++ based on DearImGui_

## Objectives
Crete a Data Visualization tool using DearImGui.

## Dependencies

Initialize all the Submodules before building.

```sh
# Initialize the Submodules
git submodule update --init --recursive
```

## Building

Running inside the Development Container, it should have the dependencies configured.

```sh
# Generate the CMake Build Files
cmake -S . -B build

# Build the project
cmake --build build
```