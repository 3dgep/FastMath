#pragma once

#include "Vector.hpp"

namespace FastMath
{

/// <summary>
/// A base class for the Matrix class template.
/// You shouldn't use this class directly. It is only used to provide
/// partial specializations of the Matrix class without having to duplicate
/// the entire Matrix class template.
/// </summary>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows of the matrix.</typeparam>
/// <typeparam name="M">(optional) The number of columns of the matrix (default to the number of
/// rows).</typeparam>
template<typename T, std::size_t N, std::size_t M = N>
struct MatrixBase
{
    constexpr MatrixBase() noexcept;

    union
    {
        Vector<T, M> row[N];
        T            m[N * M];
    };
};

/// <summary>
/// Partial specialization for matrices with 2 rows.
/// </summary>
/// <typeparam name="T">The type of the elements of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
template<typename T, std::size_t M>
struct MatrixBase<T, 2, M>
{
    constexpr MatrixBase() noexcept;

    union
    {
        struct
        {
            Vector<T, M> X, Y;
        };
        Vector<T, M> row[2];
        T            m[2 * M];
    };
};

/// <summary>
/// Partial specialization for matrices with 3 rows.
/// </summary>
/// <typeparam name="T">The type of the elements of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
template<typename T, std::size_t M>
struct MatrixBase<T, 3, M>
{
    constexpr MatrixBase() noexcept;

    union
    {
        struct
        {
            Vector<T, M> X, Y, Z;
        };
        Vector<T, M> row[3];
        T            m[3 * M];
    };
};

/// <summary>
/// Partial specialization for matrices with 4 rows.
/// </summary>
/// <typeparam name="T">The type of the elements of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
template<typename T, std::size_t M>
struct MatrixBase<T, 4, M>
{
    constexpr MatrixBase() noexcept;

    union
    {
        struct
        {
            Vector<T, M> X, Y, Z, W;
        };
        Vector<T, M> row[4];
        T            m[4 * M];
    };
};

template<typename T, std::size_t N, std::size_t M>
constexpr MatrixBase<T, N, M>::MatrixBase() noexcept
: m {}
{}

template<typename T, std::size_t M>
constexpr MatrixBase<T, 2, M>::MatrixBase() noexcept
: m {}
{}

template<typename T, std::size_t M>
constexpr MatrixBase<T, 3, M>::MatrixBase() noexcept
: m {}
{}

template<typename T, std::size_t M>
constexpr MatrixBase<T, 4, M>::MatrixBase() noexcept
: m {}
{}

}  // namespace FastMath
