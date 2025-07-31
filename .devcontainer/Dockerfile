# Use a specific Ubuntu version for reproducibility
FROM ubuntu:22.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies for C++ development, CMake, and SDL2
RUN apt-get update && apt-get install -y \
    g++ \
    gcc \
    cmake \
    gdb \
    git \
    libsdl2-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user for security
RUN useradd -ms /bin/bash vscode

# Switch to the non-root user
USER vscode

# Set the working directory
WORKDIR /home/vscode