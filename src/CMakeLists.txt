cmake_minimum_required(VERSION 3.22.1)

set( INC_ROOT ${CMAKE_SOURCE_DIR}/inc/FastMath )

set( INC
	${INC_ROOT}/Config.hpp
	${INC_ROOT}/Common.hpp
	${INC_ROOT}/Concepts.hpp
	${INC_ROOT}/VectorBase.hpp
	${INC_ROOT}/Vector.hpp
	${INC_ROOT}/MatrixBase.hpp
	${INC_ROOT}/Matrix.hpp
	${INC_ROOT}/QuaternionBase.hpp
	${INC_ROOT}/Quaternion.hpp
	${INC_ROOT}/Transform.hpp
	${INC_ROOT}/FastMath.natvis
)

set( SRC 
	FastMath.cpp
	../.clang-format
)

add_library( FastMath STATIC ${INC} ${SRC} )

target_compile_features( FastMath PUBLIC cxx_std_20 )
if(MSVC)
    target_compile_options( FastMath PUBLIC /arch:AVX2 /fp:fast PRIVATE /W4 /WX )
else()
    target_compile_options( FastMath PUBLIC -mavx2 -ffast-math PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

target_include_directories( FastMath
	PUBLIC
		${CMAKE_SOURCE_DIR}/inc
)