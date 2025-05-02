cmake_minimum_required(VERSION 3.20)
project(MyGameSolution)

if (MSVC)
	set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE "x64")

	if (USE_STATIC_MSVC_RUNTIME_LIBRARY)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	else()
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
	endif()

	if (GENERATE_DEBUG_SYMBOLS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
	endif()


	if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif()
else()
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-stringop-overflow -ffp-contract=off")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffp-model=precise")

		if (CMAKE_CXX_COMPILER_VERSION LESS 14 OR CROSS_PLATFORM_DETERMINISTIC)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffp-contract=off")
		endif()
	endif()

	set(CMAKE_CXX_FLAGS_DEBUG "")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")

	if (NOT ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows"))
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
	endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    joltphysics
    GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
    GIT_TAG v5.3.0
    SOURCE_SUBDIR "Build"
)
FetchContent_MakeAvailable(joltphysics)

# Your projects
add_subdirectory(Engine)
add_subdirectory(SideScroller)
