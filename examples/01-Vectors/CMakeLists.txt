cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

set( TARGET_NAME 01-Vectors )

set( INC
)

set( SRC
    main.cpp
)

add_executable( ${TARGET_NAME}
    ${INC} 
    ${SRC}
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/inc
)