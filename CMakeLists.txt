cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

# Version information
set(FM_VERSION_MAJOR 0)
set(FM_VERSION_MINOR 1)
set(FM_VERSION_PATCH 0)
set(FM_VERSION_TWEAK 0)

set(FM_VERSION ${FM_VERSION_MAJOR}.${FM_VERSION_MINOR}.${FM_VERSION_PATCH}.${FM_VERSION_TWEAK})

project(FastMath VERSION ${FM_VERSION} LANGUAGES CXX)

# Tests, examples, and benchmarks are only built by default when FastMath is the top-level project
# (not when it is included in another project with add_subdirectory or FetchContent).
option( FM_BUILD_EXAMPLES "Build the FastMath examples." ${PROJECT_IS_TOP_LEVEL} )
option( FM_BUILD_PERFORMANCE "Build the FastMath performance benchmarks." OFF )
option( FM_BUILD_TESTING "Build the FastMath unit tests." OFF )

# Code generation options. These are propagated to every target that links with FastMath.
option( FM_ENABLE_AVX2 "Compile targets that link with FastMath with AVX2 instructions enabled." ${PROJECT_IS_TOP_LEVEL} )
option( FM_ENABLE_FAST_MATH "Compile targets that link with FastMath with fast (non IEEE-754 compliant) floating-point math." OFF )

if(PROJECT_IS_TOP_LEVEL)
	# Use solution folders.
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# Make sure DLL and EXE targets go to the same directory.
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

	# Enable multi-processor builds in MSVC.
	if(MSVC)
		add_compile_options(/MP)
	endif()
endif()

# Compiler warnings used by the FastMath tests, examples, and benchmarks.
if(MSVC)
	set(FM_WARNINGS /W4 /WX)
else()
	set(FM_WARNINGS -Wall -Wextra -Werror -pedantic)
endif()

# FastMath library (header-only).
set( FM_INC_ROOT ${PROJECT_SOURCE_DIR}/inc/FastMath )

set( FM_INC
	${FM_INC_ROOT}/Config.hpp
	${FM_INC_ROOT}/Common.hpp
	${FM_INC_ROOT}/Concepts.hpp
	${FM_INC_ROOT}/VectorBase.hpp
	${FM_INC_ROOT}/Vector.hpp
	${FM_INC_ROOT}/MatrixBase.hpp
	${FM_INC_ROOT}/Matrix.hpp
	${FM_INC_ROOT}/QuaternionBase.hpp
	${FM_INC_ROOT}/Quaternion.hpp
	${FM_INC_ROOT}/Transform.hpp
	${FM_INC_ROOT}/FastMath.natvis
)

# Sources of an INTERFACE library are only shown in the IDE, they are not compiled.
add_library( FastMath INTERFACE ${FM_INC} )
add_library( FastMath::FastMath ALIAS FastMath )

target_compile_features( FastMath INTERFACE cxx_std_20 )

target_include_directories( FastMath
	INTERFACE
		${PROJECT_SOURCE_DIR}/inc
)

if(MSVC)
	# Add the debugger visualizers to every target that links with FastMath.
	target_sources( FastMath INTERFACE ${FM_INC_ROOT}/FastMath.natvis )
endif()

if(FM_ENABLE_AVX2)
	if(MSVC)
		target_compile_options( FastMath INTERFACE /arch:AVX2 )
	else()
		target_compile_options( FastMath INTERFACE -mavx2 )
	endif()
endif()

if(FM_ENABLE_FAST_MATH)
	if(MSVC)
		target_compile_options( FastMath INTERFACE /fp:fast )
	else()
		target_compile_options( FastMath INTERFACE -ffast-math )
	endif()
endif()

set_target_properties( FastMath PROPERTIES FOLDER FastMath )

if(FM_BUILD_TESTING)
	# Add tests.
	include(CTest)
	add_subdirectory(tests)
endif()

if(FM_BUILD_EXAMPLES)
	# Add examples project.
	add_subdirectory(examples)
endif()

if(FM_BUILD_PERFORMANCE)
	# Generate performance benchmarks.
	add_subdirectory(perf)
endif()
