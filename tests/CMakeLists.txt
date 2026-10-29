cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

# BUILD_SHARED_LIBS breaks Google Test.
set(BUILD_SHARED_LIBS OFF)
# Use the same (DLL) runtime library as the tests on MSVC.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

set( SRC
    Instantiation.cpp
    MatrixTests.cpp
    QuaternionTests.cpp
    TransformTests.cpp
    VectorTests.cpp
    ../.clang-format
)

add_executable( FastMath_tests ${SRC} )

target_compile_options( FastMath_tests PRIVATE ${FM_WARNINGS} )

target_link_libraries( FastMath_tests PRIVATE GTest::gtest_main FastMath::FastMath )

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
