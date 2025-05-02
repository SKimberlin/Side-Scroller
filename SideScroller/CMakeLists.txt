cmake_minimum_required(VERSION 3.20)
project(SideScroller)

# Ensure proper C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
file(GLOB_RECURSE GAME_SOURCES
    src/*.cpp
    src/*.h
)

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Create the SideScroller executable
add_executable(SideScroller ${GAME_SOURCES} "src/Main.cpp")

# Set the include directories for the SideScroller project
target_include_directories(SideScroller
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine  # Assuming Engine has its own includes
    ${joltphysics_SOURCE_DIR}/Core     # Include Jolt headers (core folder)
)

# Link libraries
target_link_libraries(SideScroller
    PRIVATE
    Engine
    Jolt
    raylib
)
