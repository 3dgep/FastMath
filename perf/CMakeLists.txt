cmake_minimum_required(VERSION 3.22.1)

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)

# glm is used to compare the performance of FastMath.
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)

FetchContent_MakeAvailable(benchmark glm)

set( SRC
    VectorPerf.cpp
    MatrixPerf.cpp
)

add_executable( FastMath_perf ${SRC} )

target_link_libraries( FastMath_perf PRIVATE FastMath::FastMath glm::glm benchmark::benchmark benchmark::benchmark_main )

# The benchmarks contain hand-written SSE4 intrinsics, so they always need AVX2 enabled.
if(NOT FM_ENABLE_AVX2)
    if(MSVC)
        target_compile_options( FastMath_perf PRIVATE /arch:AVX2 )
    else()
        target_compile_options( FastMath_perf PRIVATE -mavx2 )
    endif()
endif()

set_target_properties(
	benchmark
	benchmark_main
    PROPERTIES FOLDER externals/benchmark
)

set_target_properties(
    FastMath_perf
    PROPERTIES FOLDER Perf
)
