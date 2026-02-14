cmake_minimum_required(VERSION 4.1)
project(DataStructure)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers folder
include_directories(include)

# Add only .cpp source files
add_executable(DataStructure src/main.cpp
)