cmake_minimum_required(VERSION 3.23.0) # The version of CMake used when creating this project.

project( FastMath_perf )

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_INSTALL_DOCS OFF)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
FetchContent_MakeAvailable(benchmark)

set( SRC
    VectorPerf.cpp
    MatrixPerf.cpp
)

add_executable( FastMath_perf ${SRC} )

target_compile_features( FastMath_perf PUBLIC cxx_std_20 )

if(MSVC)
    target_compile_options( FastMath_perf PUBLIC /arch:AVX2 /fp:fast)
else()
    target_compile_options( FastMath_perf PUBLIC -mavx2 -ffast-math)
endif()

target_link_libraries( FastMath_perf benchmark benchmark_main )

target_include_directories( FastMath_perf
    PUBLIC ../inc
)

set_target_properties(
	benchmark
	benchmark_main
    PROPERTIES FOLDER externals/benchmark
)

set_target_properties(
    FastMath_perf
    PROPERTIES FOLDER Perf
)