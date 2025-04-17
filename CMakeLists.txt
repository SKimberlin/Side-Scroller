cmake_minimum_required(VERSION 3.20)
project(MyGameSolution)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

#Fetch Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

#Fetch JoltPhysics
FetchContent_Declare(
    joltphysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG        v5.3.0
)

FetchContent_Populate(joltphysics)

add_subdirectory(${joltphysics_SOURCE_DIR}/Build ${joltphysics_BINARY_DIR})

#Add My Directories
add_subdirectory(Engine)
add_subdirectory(SideScroller)
