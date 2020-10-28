# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (EGC_Framework)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-fPIC")

find_package(OpenGL REQUIRED)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/res)
set(CMAKE_CXX_STANDARD 11)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	file(GLOB LIB_MAC "${CMAKE_SOURCE_DIR}/external/components/*.dylib")
endif()

# Compile external dependencies
add_subdirectory (external)

link_directories(${CMAKE_SOURCE_DIR}/external/components)

include_directories(
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/stb/
	src/
	src/engine/
)

set(ALL_LIBS
	assimp
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
	STB
	Components
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_subdirectory(src)
