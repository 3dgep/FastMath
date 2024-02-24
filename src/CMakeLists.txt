cmake_minimum_required(VERSION 3.23.0) # The version of CMake used when creating this project.

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
    target_compile_options( FastMath PUBLIC /arch:AVX2 /fp:fast)
else()
    target_compile_options( FastMath PUBLIC -mavx2 -ffast-math)
endif()

target_include_directories( FastMath
	PUBLIC
		${CMAKE_SOURCE_DIR}/inc
)