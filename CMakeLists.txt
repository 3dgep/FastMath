cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

option( FASTMATH_BUILD_EXAMPLES "Build examples for LightSpeed Engine." ON )
option( FASTMATH_BUILD_DOCUMENTATION "Build the documentation for LightSpeed Engine." OFF )
option( FASTMATH_BUILD_PERFORMANCE "Build the performance benchmarks for LightSpeed Engine." OFF )
option( FASTMATH_BUILD_TESTING "Build test projects." OFF)
option( BUILD_SHARED_LIBS "Build shared libraries." ON )

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Make sure DLL and EXE targets go to the same directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Version information
set(FASTMATH_VERSION_MAJOR 0)
set(FASTMATH_VERSION_MINOR 1)
set(FASTMATH_VERSION_PATCH 0)
set(FASTMATH_VERSION_TWEAK 0)

set(FASTMATH_VERSION ${FASTMATH_VERSION_MAJOR}.${FASTMATH_VERSION_MINOR}.${FASTMATH_VERSION_PATCH}.${FASTMATH_VERSION_TWEAK})

# Use C++20 language standard.
set(CMAKE_CXX_STANDARD 20)

project(FastMath VERSION ${FASTMATH_VERSION} LANGUAGES CXX)

# Enable multi-processor builds in MSVC.
if(MSVC)
    add_compile_options(/MP)
endif(MSVC)

# Add the main source files.
add_subdirectory(src)

if(FASTMATH_BUILD_TESTING)
	# Add tests.
	include(CTest)
	add_subdirectory(tests)
endif(FASTMATH_BUILD_TESTING)

if (FASTMATH_BUILD_EXAMPLES)
	# Add examples project.
	add_subdirectory(examples)
endif(FASTMATH_BUILD_EXAMPLES )

if(FASTMATH_BUILD_PERFORMANCE)
	# Generate performance benchmarks.
	add_subdirectory(perf)
endif(FASTMATH_BUILD_PERFORMANCE)