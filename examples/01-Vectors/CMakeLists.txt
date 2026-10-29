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

target_compile_options( ${TARGET_NAME} PRIVATE ${FM_WARNINGS} )

target_link_libraries( ${TARGET_NAME} PRIVATE FastMath::FastMath )