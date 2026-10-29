#pragma once

#include "Vector.hpp"

namespace FastMath
{
/// <summary>
/// Base class for matrices.
/// </summary>
/// <remarks>
/// The matrix is stored as an array of row vectors, so `m[i]` is row `i` and `m[i][j]` is
/// the element in row `i` and column `j`.
/// </remarks>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
template<typename T, std::size_t N, std::size_t M = N>
struct MatrixBase
{
    Vector<T, M> row[N];
};

}  // namespace FastMath
