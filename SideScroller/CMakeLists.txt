project(SideScroller)

file(GLOB_RECURSE GAME_SOURCES
    src/*.cpp
    src/*.h
)

add_executable(SideScroller ${GAME_SOURCES})

target_include_directories(SideScroller
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SideScroller
    Engine
)
