cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

project( FastMath_tests )

#Enable testing
include(CTest)

# BUILD_SHARED_LIBS breaks Google Test.
set(BUILD_SHARED_LIBS OFF) 

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

set( SRC
    MatrixTests.cpp
    QuaternionTests.cpp
    VectorTests.cpp
    ../.clang-format
)

add_executable( FastMath_tests ${SRC} )

target_compile_features( FastMath_tests PUBLIC cxx_std_20 )

target_link_libraries( FastMath_tests GTest::gtest_main FastMath )
target_include_directories( FastMath_tests 
    PUBLIC ../inc
)

include(GoogleTest)
gtest_discover_tests( FastMath_tests )

set_target_properties(
    gmock
    gmock_main
    gtest
    gtest_main
    PROPERTIES FOLDER externals/gtest
)

set_target_properties(
    FastMath_tests
    PROPERTIES FOLDER Tests
)