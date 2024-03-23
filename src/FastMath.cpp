#include <FastMath/Matrix.hpp>
#include <FastMath/Quaternion.hpp>
#include <FastMath/Transform.hpp>
#include <FastMath/Vector.hpp>

namespace FastMath {
// Explicit template instantiation.
template struct Vector<float, 2>;
template struct Vector<double, 2>;
template struct Vector<int, 2>;
template struct Vector<unsigned, 2>;

template struct Vector<float, 3>;
template struct Vector<double, 3>;
template struct Vector<int, 3>;
template struct Vector<unsigned, 3>;

template struct Vector<float, 4>;
template struct Vector<double, 4>;
template struct Vector<int, 4>;
template struct Vector<unsigned, 4>;

template struct Matrix<float, 2>;
template struct Matrix<double, 2>;
template struct Matrix<int, 2>;
template struct Matrix<unsigned, 2>;

template struct Matrix<float, 3>;
template struct Matrix<double, 3>;
template struct Matrix<int, 3>;
template struct Matrix<unsigned, 3>;

template struct Matrix<float, 4>;
template struct Matrix<double, 4>;
template struct Matrix<int, 4>;
template struct Matrix<unsigned, 4>;

template struct Quaternion<float>;
template struct Quaternion<double>;

template struct Transform<float>;
template struct Transform<double>;

}