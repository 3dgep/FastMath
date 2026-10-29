#pragma once

#include "MatrixBase.hpp"

#include <cassert>
#include <compare>
#include <initializer_list>
#include <utility>

namespace FastMath
{

/// <summary>
/// Define an \f(n \times m\f) matrix with \f(n\f) rows and \f(m\f) columns.
/// The matrix is stored in row-major so that we can use `M[i][j]`
/// to access the \f(i^{th}\f) row and \f(j^{th}\f) column of the matrix.
/// </summary>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
template<typename T, std::size_t N, std::size_t M = N>
struct Matrix : MatrixBase<T, N, M>
{
    /// <summary>
    /// The type of the matrix elements.
    /// </summary>
    using value_type = T;

    /// <summary>
    /// The type used to represent the size of the matrix.
    /// </summary>
    using size_type = std::size_t;

    /// <summary>
    /// The base class of the matrix (used internally).
    /// </summary>
    using base = MatrixBase<T, N, M>;

    /// <summary>
    /// The rank of the matrix. The rank is `min(N, M)`, that is, either the number of
    /// rows or number of columns of the matrix (whichever is less).
    /// </summary>
    static constexpr std::size_t rank = std::min( N, M );

    /// <summary>
    /// An \f(n \times m\f) identity matrix.
    /// The diagonal of the matrix contains `1`'s and the rest of the
    /// matrix contains `0`'s.
    /// </summary>
    /// <typeparam name="T">The type of the values of the matrix.</typeparam>
    /// <typeparam name="N">The number of rows of the matrix.</typeparam>
    /// <typeparam name="M">The number of columns of the matrix.</typeparam>
    static const Matrix<T, N, M> IDENTITY;

    /// <summary>
    /// Get the number of elements in the matrix.
    /// </summary>
    /// <returns>The number of elements of the matrix (`N`*`M`)</returns>
    constexpr std::size_t size() const noexcept;

    /// <summary>
    /// Get a pointer to the first element of the matrix.
    /// </summary>
    /// <returns>A pointer to the first element of the matrix.</returns>
    constexpr T* data() noexcept;

    /// <summary>
    /// Get a pointer to the first element of the matrix.
    /// </summary>
    /// <returns>A pointer to the first element of the matrix.</returns>
    constexpr const T* data() const noexcept;

    /// <summary>
    /// Default-construct a Matrix.
    /// All of the values of the matrix are initialized to `0`.
    /// </summary>
    constexpr Matrix() noexcept;

    /// <summary>
    /// Construct a Matrix with `s` copied to the main diagonal of the Matrix.
    /// </summary>
    /// <remarks>
    /// To ensure the compiler chooses this constructor over the one that takes an `std::initializer_list`,
    /// the Matrix must be constructed like this:
    /// <code>
    /// Matrix4f m( x );        // Do not use direct-list-initialization.
    /// auto m = Matrix4f( x ); // Do not use copy-list-initialization.
    /// </code>
    /// See <a href="https://en.cppreference.com/w/cpp/utility/initializer_list">`std::initializer_list`</a> for more information
    /// about initializer lists and when an `std::initializer_list` is used.
    /// </remarks>
    /// <param name="s">The value to copy to the main diagonal of the Matrix.</param>
    template<ConvertibleTo<T> U>
    explicit constexpr Matrix( U s ) noexcept;

    /// <summary>
    /// Construct a matrix from an `std::span`.
    /// The span must contain values that are convertible to `T`.
    /// This allows matrices to be constructed from `std::vector` or
    /// `std::array` (or anything that can be stored in a span).
    /// </summary>
    /// <param name="s">The span of values.</param>
    template<ConvertibleTo<T> U, std::size_t S>
    constexpr Matrix( std::span<U, S> s ) noexcept;

    /// <summary>
    /// Construct a matrix from an `std::initializer_list`. This allows
    /// matrices to be constructed like this:
    /// <code>
    /// Matrix2f a = {
    ///     1, 2,
    ///     3, 4
    /// };
    /// </code>
    /// </summary>
    /// <typeparam name="U">The type of values of the initializer list. `U` must be
    /// convertible to `T`.</typeparam>
    template<ConvertibleTo<T> U>
    constexpr Matrix( std::initializer_list<U> l ) noexcept;

    /// <summary>
    /// Construct a matrix from a list of std::initializer_list. This allows
    /// matrices to be constructed like this:
    /// <code>
    /// Matrix2f a = { { 1, 2 }, { 3, 4 } };
    /// </code>
    /// </summary>
    /// <typeparam name="U">The type of values of the initializer list. `U` must be
    /// convertible to `T`.</typeparam>
    template<ConvertibleTo<T> U>
    constexpr Matrix( std::initializer_list<std::initializer_list<U>> ll ) noexcept;

    /// <summary>
    /// Construct a matrix from a list of vectors. This allows matrices to be constructed
    /// like this:
    /// <code>
    /// Matrix3f a = { v1, v2, v3 };
    /// </code>
    /// Where v1, v2, and v3 are Vectors.
    /// </summary>
    template<ConvertibleTo<T> U>
    constexpr Matrix( std::initializer_list<Vector<U, M>> l ) noexcept;

    /// <summary>
    /// Copy constructor allows arbitrary sized Matrices to be copied. Only the top-left
    /// overlapping portion of the matrix is copied.
    /// </summary>
    /// <param name="copy">The matrix to be copied.</param>
    template<ConvertibleTo<T> U, std::size_t I, std::size_t J>
    constexpr Matrix( const Matrix<U, I, J>& copy ) noexcept;

    /// <summary>
    /// Copy the submatrix that results by removing the \f(i^{th}\f) row and the
    /// \f(j^{th}\f) column of the original matrix.
    /// </summary>
    /// <param name="copy">The matrix to copy.</param>
    /// <param name="i">The row to remove from `copy`.</param>
    /// <param name="j">The column to remove from `copy`.</param>
    template<ConvertibleTo<T> U>
    constexpr Matrix( const Matrix<U, N + 1, M + 1>& copy, std::size_t i, std::size_t j ) noexcept;

    /// <summary>
    /// Assign an arbitrarily sized matrix to this one. Only the top-left overlapping
    /// portion of the matrix is copied to this one.
    /// \f[
    /// \mathbf{M}_{ij} = \mathbf{A}_{ij}
    /// \f]
    /// For each \f(i\f), \f(j\f) (whichever is smallest).
    /// </summary>
    /// <typeparam name="U">The type of the components of the right-hand
    /// matrix.</typeparam> <typeparam name="I">The number of rows of the right-hand
    /// matrix.</typeparam> <typeparam name="J">The number of columns of the right-hand
    /// matrix.</typeparam> <param name="rhs">The matrix to assign to this one.</param>
    template<ConvertibleTo<T> U, std::size_t I, std::size_t J>
    constexpr Matrix<T, N, M>& operator=( const Matrix<U, I, J>& rhs ) noexcept;

    /// <summary>
    /// Access the \f(i^{th}\f) row of the matrix.
    /// \f[
    /// \mathbf{v} = \mathbf{M}_{i}
    /// \f]
    /// </summary>
    /// <param name="i">The index of the row to retrieve.</param>
    /// <returns>The \f(i^{th}\f) row of the matrix (as a Vector)</returns>
    constexpr Vector<T, M>& operator[]( std::size_t i ) noexcept;

    /// <summary>
    /// Access the \f(i^{th}\f) row of the matrix.
    /// \f[
    /// \mathbf{v} = \mathbf{M}_{i}
    /// \f]
    /// </summary>
    /// <param name="i">The index of the row to retrieve.</param>
    /// <returns>The \f(i^{th}\f) row of the matrix (as a Vector)</returns>
    constexpr const Vector<T, M>& operator[]( std::size_t i ) const noexcept;

    /// <summary>
    /// Unary plus. This just returns a copy of the matrix:
    /// \f[
    /// \mathbf{M} = \mathbf{A}
    /// \f]
    /// </summary>
    /// <returns>A copy of this matrix.</returns>
    constexpr Matrix<T, N, M> operator+() const noexcept;

    /// <summary>
    /// Unary minus. Negate each element of the matrix.
    /// \f[
    /// \mathbf{M}_{ij} = -\mathbf{A}_{ij}
    /// \f]
    /// </summary>
    /// <returns>A matrix with each element of this matrix negated.</returns>
    constexpr Matrix<T, N, M> operator-() const noexcept
        requires IsSigned<T>;

    /// <summary>
    /// Add this matrix and another and assign the result back to this matrix.
    /// \f[
    /// \mathbf{M}_{ij} = \mathbf{M}_{ij} + \mathbf{A}_{ij}
    /// \f]
    /// </summary>
    /// <param name="rhs">The matrix on the right-hand side of the `+=` operator.</param>
    /// <returns>A reference to this matrix.</returns>
    constexpr Matrix<T, N, M>& operator+=( const Matrix<T, N, M>& rhs ) noexcept;

    /// <summary>
    /// Subtract a matrix from this matrix and store the result in this matrix.
    /// \f[
    /// \mathbf{M}_{ij} = \mathbf{M}_{ij} - \mathbf{A}_{ij}
    /// \f]
    /// </summary>
    /// <param name="rhs">The matrix to subtract from this matrix.</param>
    /// <returns>A reference to this matrix.</returns>
    constexpr Matrix<T, N, M>& operator-=( const Matrix<T, N, M>& rhs ) noexcept;

    /// <summary>
    /// Scalar matrix multiplication and assignment. Each component of this matrix is
    /// multiplied by the scalar \f(s\f) and assigned back to this matrix.
    /// \f[
    /// \mathbf{M}_{ij} = s\mathbf{M}_{ij}
    /// \f]
    /// </summary>
    /// <param name="s">The scalar to multiply.</param>
    /// <returns>A reference to this matrix after scalar multiplication.</returns>
    constexpr Matrix<T, N, M>& operator*=( T s ) noexcept;

    /// <summary>
    /// Scalar matrix division and assignment. Each component of the matrix is divided by
    /// the scalar \f(s\f) then assigned back to this matrix. \f[ \mathbf{M}_{ij} =
    /// \frac{\mathbf{A}_{ij}}{s} \f]
    /// </summary>
    /// <remarks>
    /// `s` must not be 0.
    /// </remarks>
    /// <param name="s">The scalar to divide each component of the matrix.</param>
    /// <returns>A reference to this matrix after scalar division.</returns>
    constexpr Matrix<T, N, M>& operator/=( T s ) noexcept;

    /// <summary>
    /// Multiply this matrix by another and store the result in this matrix.
    /// \f[
    /// \mathbf{M}_{ij} = \sum_{k=1}^{m}\mathbf{M}_{ik}\mathbf{A}_{kj}
    /// \f]
    /// </summary>
    /// <remarks>
    /// Since the resulting matrix must be an \f(n \times m\f) matrix, this operator can
    /// only be applied to an \f(m \times m\f) matrix.
    /// </remarks>
    /// <param name="rhs">The matrix to multiply.</param>
    /// <returns>A reference to this matrix after multiplication.</returns>
    constexpr Matrix<T, N, M>& operator*=( const Matrix<T, M, M>& rhs ) noexcept;

    // The binary operators are hidden friends: they are only found by argument-dependent lookup
    // when one of the operands is a Matrix<T, N, M>. This keeps overload resolution (and compile errors)
    // small, and allows the scalar to be on either side of the operator.

    /// <summary>
    /// Add two matrices:
    /// \f[
    /// \mathbf{M}_{ij} = \mathbf{A}_{ij} + \mathbf{B}_{ij}
    /// \f]
    /// </summary>
    /// <param name="lhs">The matrix on the left-hand side of the `+` operator.</param>
    /// <param name="rhs">The matrix on the right-hand side of the `+` operator.</param>
    /// <returns>The result of adding the two matrices.</returns>
    friend constexpr Matrix<T, N, M> operator+( Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs ) noexcept
    {
        return lhs += rhs;
    }

    /// <summary>
    /// Subtract two matrices.
    /// \f[
    /// \mathbf{M}_{ij} = \mathbf{A}_{ij} - \mathbf{B}_{ij}
    /// \f]
    /// </summary>
    /// <param name="lhs">The matrix to subtract from.</param>
    /// <param name="rhs">The matrix to subtract.</param>
    /// <returns>The result of subtracting `rhs` from `lhs`.</returns>
    friend constexpr Matrix<T, N, M> operator-( Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs ) noexcept
    {
        return lhs -= rhs;
    }

    /// <summary>
    /// Scalar matrix multiplication. Each component of the matrix is multiplied by the
    /// scalar \f(s\f).
    /// \f[
    /// \mathbf{M}_{ij} = s\mathbf{A}_{ij}
    /// \f]
    /// </summary>
    /// <param name="lhs">The matrix.</param>
    /// <param name="s">The scalar to multiply.</param>
    /// <returns>The result of multiplying the matrix by the scalar \f(s\f).</returns>
    friend constexpr Matrix<T, N, M> operator*( Matrix<T, N, M> lhs, T s ) noexcept
    {
        return lhs *= s;
    }

    /// <summary>
    /// Scalar matrix multiplication. Each component of the matrix is multiplied by the
    /// scalar \f(s\f).
    /// \f[
    /// \mathbf{M}_{ij} = s\mathbf{A}_{ij}
    /// \f]
    /// </summary>
    /// <param name="s">The scalar to multiply.</param>
    /// <param name="rhs">The matrix.</param>
    /// <returns>The result of multiplying the matrix by the scalar \f(s\f).</returns>
    friend constexpr Matrix<T, N, M> operator*( T s, Matrix<T, N, M> rhs ) noexcept
    {
        return rhs *= s;
    }

    /// <summary>
    /// Scalar matrix division. Each component of the matrix is divided by the scalar
    /// \f(s\f). \f[ \mathbf{M}_{ij} = \frac{\mathbf{A}_{ij}}{s} \f]
    /// </summary>
    /// <remarks>
    /// `s` must not be 0.
    /// </remarks>
    /// <param name="lhs">The matrix.</param>
    /// <param name="s">The scalar to divide each component of the matrix.</param>
    /// <returns>The result of dividing the matrix by \f(s\f).</returns>
    friend constexpr Matrix<T, N, M> operator/( Matrix<T, N, M> lhs, T s ) noexcept
    {
        return lhs /= s;
    }

    /// <summary>
    /// Multiply a matrix with a column-vector (on the right).
    /// \f[
    /// \mathbf{v}^{\prime}_{i} = \sum_{k=1}^{m}\mathbf{M}_{ik}\mathbf{v}_{k}
    /// \f]
    /// </summary>
    /// <param name="lhs">The matrix.</param>
    /// <param name="rhs">The column vector to multiply.</param>
    /// <returns>The resulting column vector.</returns>
    friend constexpr Vector<T, N> operator*( const Matrix<T, N, M>& lhs, const Vector<T, M>& rhs ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = dot( lhs.row[i], rhs );

        return res;
    }

    /// <summary>
    /// Multiply a row-vector (on the left) with a matrix.
    /// \f[
    /// \mathbf{v}^{\prime}_{j} = \sum_{k=1}^{n}\mathbf{v}_{k}\mathbf{M}_{kj}
    /// \f]
    /// </summary>
    /// <param name="lhs">The row vector to multiply.</param>
    /// <param name="rhs">The matrix.</param>
    /// <returns>The resulting row vector.</returns>
    friend constexpr Vector<T, M> operator*( const Vector<T, N>& lhs, const Matrix<T, N, M>& rhs ) noexcept
    {
        Vector<T, M> res;

        for ( std::size_t i = 0; i < N; ++i )
            res += lhs[i] * rhs.row[i];

        return res;
    }

    /// <summary>
    /// Multiply two matrices.
    /// If \f(\mathbf{A}\f) is an \f(n \times m\f) matrix and \f(\mathbf{B}\f) is an \f(m
    /// \times p\f) matrix, then the resulting matrix is \f(n \times p\f). \f[
    /// \mathbf{M}_{ij} = \sum_{k=1}^{m}\mathbf{A}_{ik}\mathbf{B}_{kj}
    /// \f]
    /// </summary>
    /// <typeparam name="P">The number of columns in the right matrix.</typeparam>
    /// <param name="lhs">The matrix on the left.</param>
    /// <param name="rhs">The matrix on the right.</param>
    /// <returns>The \f(n \times p\f) product of the two matrices.</returns>
    template<std::size_t P>
    friend constexpr Matrix<T, N, P> operator*( const Matrix<T, N, M>& lhs, const Matrix<T, M, P>& rhs ) noexcept
    {
        Matrix<T, N, P> res {};

        for ( std::size_t i = 0; i < N; ++i )
            for ( std::size_t j = 0; j < P; ++j )
                for ( std::size_t k = 0; k < M; ++k )
                    res.row[i][j] += lhs.row[i][k] * rhs.row[k][j];

        return res;
    }

    /// <summary>
    /// Check if two matrices are the same.
    /// </summary>
    /// <param name="lhs">The first matrix to compare.</param>
    /// <param name="rhs">The second matrix to compare.</param>
    /// <returns>`true` if the matrices are equal, `false` otherwise.</returns>
    friend constexpr bool operator==( const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs ) noexcept
    {
        for ( std::size_t i = 0; i < N; ++i )
            if ( lhs.row[i] != rhs.row[i] )
                return false;

        return true;
    }

    /// <summary>
    /// Construct a diagonal matrix.
    /// \f[
    /// M_{m,n} = \begin{pmatrix}
    /// x & 0 & \cdots & 0 \\ 0 & x & \cdots & 0 \\ \vdots & \vdots & \ddots & \vdots \\ 0 & 0 & \cdots & x
    /// \end{pmatrix}
    /// \f]
    /// </summary>
    /// <param name="x">(optional) The value to initialize the diagonal with. The default value is
    /// `1` to generate an identity matrix.</param>
    /// <returns>A diagonal matrix with `x` as the values along the diagonal.</returns>
    template<ConvertibleTo<T> U>
    static constexpr Matrix<T, N, M> diagonal( U x = U( 1 ) ) noexcept;
};

using Matrix2f = Matrix<float, 2>;
using Matrix2d = Matrix<double, 2>;
using Matrix2i = Matrix<int32_t, 2>;
using Matrix2u = Matrix<uint32_t, 2>;

using Matrix3f = Matrix<float, 3>;
using Matrix3d = Matrix<double, 3>;
using Matrix3i = Matrix<int32_t, 3>;
using Matrix3u = Matrix<uint32_t, 3>;

using Matrix4f = Matrix<float, 4>;
using Matrix4d = Matrix<double, 4>;
using Matrix4i = Matrix<int32_t, 4>;
using Matrix4u = Matrix<uint32_t, 4>;

using float2x2 = Matrix<float, 2, 2>;
using float2x3 = Matrix<float, 2, 3>;
using float2x4 = Matrix<float, 2, 4>;
using float3x2 = Matrix<float, 3, 2>;
using float3x3 = Matrix<float, 3, 3>;
using float3x4 = Matrix<float, 3, 4>;
using float4x2 = Matrix<float, 4, 2>;
using float4x3 = Matrix<float, 4, 3>;
using float4x4 = Matrix<float, 4, 4>;

using double2x2 = Matrix<double, 2, 2>;
using double2x3 = Matrix<double, 2, 3>;
using double2x4 = Matrix<double, 2, 4>;
using double3x2 = Matrix<double, 3, 2>;
using double3x3 = Matrix<double, 3, 3>;
using double3x4 = Matrix<double, 3, 4>;
using double4x2 = Matrix<double, 4, 2>;
using double4x3 = Matrix<double, 4, 3>;
using double4x4 = Matrix<double, 4, 4>;

using int2x2 = Matrix<int32_t, 2, 2>;
using int2x3 = Matrix<int32_t, 2, 3>;
using int2x4 = Matrix<int32_t, 2, 4>;
using int3x2 = Matrix<int32_t, 3, 2>;
using int3x3 = Matrix<int32_t, 3, 3>;
using int3x4 = Matrix<int32_t, 3, 4>;
using int4x2 = Matrix<int32_t, 4, 2>;
using int4x3 = Matrix<int32_t, 4, 3>;
using int4x4 = Matrix<int32_t, 4, 4>;

using uint2x2 = Matrix<uint32_t, 2, 2>;
using uint2x3 = Matrix<uint32_t, 2, 3>;
using uint2x4 = Matrix<uint32_t, 2, 4>;
using uint3x2 = Matrix<uint32_t, 3, 2>;
using uint3x3 = Matrix<uint32_t, 3, 3>;
using uint3x4 = Matrix<uint32_t, 3, 4>;
using uint4x2 = Matrix<uint32_t, 4, 2>;
using uint4x3 = Matrix<uint32_t, 4, 3>;
using uint4x4 = Matrix<uint32_t, 4, 4>;

using mat2   = Matrix<float, 2>;
using mat2x2 = Matrix<float, 2, 2>;
using mat2x3 = Matrix<float, 2, 3>;
using mat2x4 = Matrix<float, 2, 4>;

using mat3   = Matrix<float, 3>;
using mat3x2 = Matrix<float, 3, 2>;
using mat3x3 = Matrix<float, 3, 3>;
using mat3x4 = Matrix<float, 3, 4>;

using mat4   = Matrix<float, 4>;
using mat4x2 = Matrix<float, 4, 2>;
using mat4x3 = Matrix<float, 4, 3>;
using mat4x4 = Matrix<float, 4, 4>;

using dmat2   = Matrix<double, 2>;
using dmat2x2 = Matrix<double, 2, 2>;
using dmat2x3 = Matrix<double, 2, 3>;
using dmat2x4 = Matrix<double, 2, 4>;

using dmat3   = Matrix<double, 3>;
using dmat3x2 = Matrix<double, 3, 2>;
using dmat3x3 = Matrix<double, 3, 3>;
using dmat3x4 = Matrix<double, 3, 4>;

using dmat4   = Matrix<double, 4>;
using dmat4x2 = Matrix<double, 4, 2>;
using dmat4x3 = Matrix<double, 4, 3>;
using dmat4x4 = Matrix<double, 4, 4>;

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U>
constexpr Matrix<T, N, M> Matrix<T, N, M>::diagonal( U x ) noexcept
{
    Matrix<T, N, M> res {};

    for ( std::size_t i = 0; i < rank; ++i )
        res.row[i][i] = static_cast<T>( x );

    return res;
}

template<typename T, std::size_t N, std::size_t M>
constexpr std::size_t Matrix<T, N, M>::size() const noexcept
{
    return N * M;
}

template<typename T, std::size_t N, std::size_t M>
constexpr T* Matrix<T, N, M>::data() noexcept
{
    static_assert( sizeof( Matrix<T, N, M> ) == N * M * sizeof( T ), "The elements must be tightly packed." );
    return &base::row[0][0];
}

template<typename T, std::size_t N, std::size_t M>
constexpr const T* Matrix<T, N, M>::data() const noexcept
{
    static_assert( sizeof( Matrix<T, N, M> ) == N * M * sizeof( T ), "The elements must be tightly packed." );
    return &base::row[0][0];
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>::Matrix() noexcept = default;

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U>
constexpr Matrix<T, N, M>::Matrix( U s ) noexcept
{
    for ( std::size_t i = 0; i < rank; ++i )
        base::row[i][i] = static_cast<T>( s );
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> X, std::size_t S>
constexpr Matrix<T, N, M>::Matrix( std::span<X, S> s ) noexcept
{
    constexpr std::size_t c = std::min( N * M, s.size() );

    // The inner loop has a constant trip count, so the column index is known at compile time after unrolling.
    for ( std::size_t i = 0; i < N; ++i )
        for ( std::size_t j = 0; j < M; ++j )
            if ( i * M + j < c )
                base::row[i][j] = static_cast<T>( s[i * M + j] );
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> X>
constexpr Matrix<T, N, M>::Matrix( std::initializer_list<X> l ) noexcept
{
    const std::size_t c = std::min( N * M, l.size() );
    const X*          x = std::data( l );

    // The inner loop has a constant trip count, so the column index is known at compile time after unrolling.
    for ( std::size_t i = 0; i < N; ++i )
        for ( std::size_t j = 0; j < M; ++j )
            if ( i * M + j < c )
                base::row[i][j] = static_cast<T>( x[i * M + j] );
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U>
constexpr Matrix<T, N, M>::Matrix( std::initializer_list<std::initializer_list<U>> ll ) noexcept
{
    std::size_t n = std::min( N, ll.size() );
    const auto  l = std::data( ll );

    for ( std::size_t i = 0; i < n; ++i )
    {
        const std::size_t m = std::min( M, l[i].size() );
        const U*          v = std::data( l[i] );
        for ( std::size_t j = 0; j < m; ++j )
            base::row[i][j] = static_cast<T>( v[j] );
    }
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U>
constexpr Matrix<T, N, M>::Matrix( std::initializer_list<Vector<U, M>> l ) noexcept
{
    std::size_t         n = std::min( N, l.size() );
    const Vector<U, M>* v = std::data( l );

    for ( std::size_t i = 0; i < n; ++i )
        base::row[i] = v[i];
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> X, std::size_t I, std::size_t J>
constexpr Matrix<T, N, M>::Matrix( const Matrix<X, I, J>& copy ) noexcept
{
    constexpr std::size_t n = std::min( N, I );
    constexpr std::size_t m = std::min( M, J );

    for ( std::size_t i = 0; i < n; ++i )
        for ( std::size_t j = 0; j < m; ++j )
            base::row[i][j] = static_cast<T>( copy.row[i][j] );

    for ( std::size_t k = std::min( n, m ); k < rank; ++k )
        base::row[k][k] = T( 1 );
}

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U>
constexpr Matrix<T, N, M>::Matrix( const Matrix<U, N + 1, M + 1>& copy, std::size_t i, std::size_t j ) noexcept
{
    std::size_t dstRow = 0;
    for ( std::size_t srcRow = 0; srcRow <= N; ++srcRow )
    {
        if ( srcRow == i )
            continue;

        std::size_t dstCol = 0;
        for ( std::size_t srcCol = 0; srcCol <= M; ++srcCol )
        {
            if ( srcCol != j )
                base::row[dstRow][dstCol++] = static_cast<T>( copy.row[srcRow][srcCol] );
        }

        ++dstRow;
    }
}

// IDENTITY is defined after the constructors so it can be evaluated at compile time.
template<typename T, std::size_t N, std::size_t M>
inline constexpr Matrix<T, N, M> Matrix<T, N, M>::IDENTITY = diagonal<T>();

template<typename T, std::size_t N, std::size_t M>
template<ConvertibleTo<T> U, std::size_t I, std::size_t J>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator=( const Matrix<U, I, J>& rhs ) noexcept
{
    constexpr std::size_t n = std::min( N, I );
    constexpr std::size_t m = std::min( M, J );

    for ( std::size_t i = 0; i < n; ++i )
        for ( std::size_t j = 0; j < m; ++j )
            base::row[i][j] = static_cast<T>( rhs.row[i][j] );

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Vector<T, M>& Matrix<T, N, M>::operator[]( std::size_t i ) noexcept
{
    assert( i < N );
    return base::row[i];
}

template<typename T, std::size_t N, std::size_t M>
constexpr const Vector<T, M>& Matrix<T, N, M>::operator[]( std::size_t i ) const noexcept
{
    assert( i < N );
    return base::row[i];
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M> Matrix<T, N, M>::operator+() const noexcept
{
    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M> Matrix<T, N, M>::operator-() const noexcept
    requires IsSigned<T>
{
    Matrix<T, N, M> res;

    for ( std::size_t i = 0; i < N; ++i )
        res.row[i] = -base::row[i];

    return res;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator+=( const Matrix<T, N, M>& rhs ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        base::row[i] += rhs.row[i];

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator-=( const Matrix<T, N, M>& rhs ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        base::row[i] -= rhs.row[i];

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator*=( T s ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        base::row[i] *= s;

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator/=( T s ) noexcept
{
    assert( s != T( 0 ) );

    for ( std::size_t i = 0; i < N; ++i )
        base::row[i] /= s;

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator*=( const Matrix<T, M, M>& rhs ) noexcept
{
    *this = *this * rhs;

    return *this;
}

/// <summary>
/// Transpose a matrix.
/// </summary>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows of the matrix.</typeparam>
/// <typeparam name="M">The number of columns of the matrix.</typeparam>
/// <param name="m">The matrix to transpose.</param>
/// <returns>The \f(m \times n\f) transposed matrix.</returns>
template<typename T, std::size_t N, std::size_t M>
constexpr Matrix<T, M, N> transpose( const Matrix<T, N, M>& m ) noexcept
{
    Matrix<T, M, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        for ( std::size_t j = 0; j < M; ++j )
            res.row[j][i] = m.row[i][j];

    return res;
}

/// <summary>
/// Compute the matrix determinant.
/// </summary>
/// <remarks>
/// Matrix determinant is only valid for square matrices.
/// </remarks>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows and columns of the matrix.</typeparam>
/// <param name="m">The matrix to compute the determinant for.</param>
/// <returns>The determinant of the matrix.</returns>
template<typename T, std::size_t N>
constexpr T determinant( const Matrix<T, N, N>& m ) noexcept
{
    if constexpr ( N == 1 )
    {
        return m.row[0][0];
    }
    else if constexpr ( N == 2 )
    {
        return m.row[0][0] * m.row[1][1] - m.row[0][1] * m.row[1][0];
    }
    else
    {
        // Cofactor expansion along the first row.
        T det = T( 0 );

        for ( std::size_t j = 0; j < N; ++j )
        {
            const T c = j % 2 == 0 ? T( 1 ) : T( -1 );
            det += m.row[0][j] * c * determinant( Matrix<T, N - 1, N - 1> { m, 0, j } );
        }

        return det;
    }
}

/// <summary>
/// Compute the adjugate of a matrix. The adjugate matrix is the transpose of the cofactor matrix.
/// </summary>
/// <remarks>
/// The adjugate matrix is only valid for square matrices.
/// </remarks>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows and columns of the matrix.</typeparam>
/// <param name="m">The matrix to compute the adjugate.</param>
/// <returns>The adjugate matrix.</returns>
template<typename T, std::size_t N>
constexpr Matrix<T, N, N> adjugate( const Matrix<T, N, N>& m ) noexcept
    requires( N > 1 )
{
    Matrix<T, N, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        for ( std::size_t j = 0; j < N; ++j )
        {
            const T c        = ( i + j ) % 2 == 0 ? T( 1 ) : T( -1 );
            res.row[j][i] = c * determinant( Matrix<T, N - 1, N - 1> { m, i, j } );
        }

    return res;
}

/// <summary>
/// Compute the inverse of a matrix.
/// </summary>
/// <remarks>
/// Matrix inverse is only valid for square matrices.
/// If the matrix is singular (the determinant is 0), the original matrix is returned.
/// </remarks>
/// <typeparam name="T">The type of the matrix elements.</typeparam>
/// <typeparam name="N">The number of rows and columns of the matrix.</typeparam>
/// <param name="m">The matrix to invert.</param>
/// <returns>The inverse of the matrix.</returns>
template<typename T, std::size_t N>
constexpr Matrix<T, N, N> inverse( const Matrix<T, N, N>& m ) noexcept
{
    if constexpr ( N == 1 )
    {
        // The inverse of a 1x1 matrix is the reciprocal of the single entry of the matrix.
        return Matrix<T, 1, 1>( T( 1 ) / m.row[0][0] );
    }
    else
    {
        // First compute the adjugate of the matrix.
        const Matrix<T, N, N> adj = adjugate( m );

        // Next, compute the determinant based on the adjugate matrix.
        T det = T( 0 );

        for ( std::size_t j = 0; j < N; ++j )
            det += m.row[0][j] * adj.row[j][0];

        if ( det != T( 0 ) )
            return adj / det;

        assert( false && "Matrix is singular." );

        // All code paths must return a value.
        return m;
    }
}

/// <summary>
/// Construct a 4x4 translation matrix.
/// \f[ \mathbf{T}_\mathbf{t} = \begin{bmatrix}
/// 1 & 0 & 0 & t_x \\ 0 & 1 & 0 & t_y \\ 0 & 0 & 1 & t_z \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="t">The translation vector.</param>
/// <returns>A translation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> translate( const Vector<T, 3>& t ) noexcept
{
    return {
        T( 1 ), T( 0 ), T( 0 ), t.x,
        T( 0 ), T( 1 ), T( 0 ), t.y,
        T( 0 ), T( 0 ), T( 1 ), t.z,
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Construct a 4x4 scale matrix.
/// \f[ \mathbf{S}_\mathbf{s} = \begin{bmatrix}
/// s_x & 0 & 0 & 0 \\ 0 & s_y & 0 & 0 \\ 0 & 0 & s_z & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="s">The scale vector.</param>
/// <returns>A scale matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> scale( const Vector<T, 3>& s ) noexcept
{
    return {
        s.x, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), s.y, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), s.z, T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Construct a matrix that performs a rotation about the X axis.
/// \f[ \mathbf{R}_x = \begin{bmatrix}
/// 1 & 0 & 0 & 0 \\ 0 & \cos{\theta} & -\sin{\theta} & 0 \\ 0 & \sin{\theta} & \cos{\theta} & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="angle">The angle of rotation (in radians).</param>
/// <returns>A rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> rotateX( T angle ) noexcept
{
    const T c = std::cos( angle );
    const T s = std::sin( angle );

    return {
        T( 1 ), T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), c, -s, T( 0 ),
        T( 0 ), s, c, T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Construct a matrix that performs a rotation about the Y axis.
/// \f[ \mathbf{R}_y = \begin{bmatrix}
/// \cos{\theta} & 0 & \sin{\theta} & 0 \\ 0 & 1 & 0 & 0 \\ -\sin{\theta} & 0 & \cos{\theta} & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="angle">The angle of rotation (in radians).</param>
/// <returns>A rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> rotateY( T angle ) noexcept
{
    const T c = std::cos( angle );
    const T s = std::sin( angle );

    return {
        c, T( 0 ), s, T( 0 ),
        T( 0 ), T( 1 ), T( 0 ), T( 0 ),
        -s, T( 0 ), c, T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Construct a matrix that performs a rotation about the Z axis.
/// \f[ \mathbf{R}_z = \begin{bmatrix}
/// \cos{\theta} & -\sin{\theta} & 0 & 0 \\ \sin{\theta} & \cos{\theta} & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="angle">The angle of rotation (in radians).</param>
/// <returns>A rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> rotateZ( T angle ) noexcept
{
    const T c = std::cos( angle );
    const T s = std::sin( angle );

    return {
        c, -s, T( 0 ), T( 0 ),
        s, c, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Construct a matrix that performs a rotation about an arbitrary axis (\f(\hat{\mathbf{v}}\f)).
/// \f[ \mathbf{R}_{\hat{\mathbf{v}}\theta} = \begin{bmatrix}
/// tx^2 + c & txy - sz & txz + sy & 0 \\ txy + sz & ty^2 + c & tyz - sx & 0 \\ txz - sy & tyz + sx & tz^2 + c & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// Where:
/// * \f(\hat{\mathbf{v}} = (x, y, z)\f)
/// * \f(c = \cos{\theta}\f)
/// * \f(s = \sin{\theta}\f)
/// * \f(t = 1 - \cos{\theta}\f)
/// </summary>
/// <remarks>
/// It is assumed that the `axis` is normalized.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="axis">The axis of rotation.</param>
/// <param name="angle">The angle of rotation (in radians).</param>
/// <returns>A rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> rotateAxisAngle( const Vector<T, 3>& axis, T angle ) noexcept
{
    assert( isNormalized( axis ) && "Axis must be normalized" );

    const T c  = std::cos( angle );
    const T s  = std::sin( angle );
    const T t  = T( 1 ) - c;
    const T x  = axis.x;
    const T y  = axis.y;
    const T z  = axis.z;
    const T sx = s * x;
    const T sy = s * y;
    const T sz = s * z;
    const T xx = x * x;
    const T xy = x * y;
    const T xz = x * z;
    const T yy = y * y;
    const T yz = y * z;
    const T zz = z * z;

    return {
        t * xx + c, t * xy - sz, t * xz + sy, T( 0 ),
        t * xy + sz, t * yy + c, t * yz - sx, T( 0 ),
        t * xz - sy, t * yz + sx, t * zz + c, T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Creates a left-handed frustum projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2n}{r-l} & 0 & -\frac{r+l}{r-l} & 0 \\ 0 & \frac{2n}{t-b} & -\frac{t+b}{t-b} & 0 \\ 0 & 0 & \frac{f}{f-n} & -\frac{fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used for DirectX, Vulkan, and Metal.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed frustum matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> frustumLH01( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / ( r - l ), T( 0 ), -( r + l ) / ( r - l ), T( 0 ),
        T( 0 ), T( 2 ) * n / ( t - b ), -( t + b ) / ( t - b ), T( 0 ),
        T( 0 ), T( 0 ), f / ( f - n ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Creates a left-handed frustum projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2n}{r-l} & 0 & -\frac{r+l}{r-l} & 0 \\ 0 & \frac{2n}{t-b} & -\frac{t+b}{t-b} & 0 \\ 0 & 0 & \frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a left-handed projection matrix for use in OpenGL.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed frustum matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> frustumLH11( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / ( r - l ), T( 0 ), -( r + l ) / ( r - l ), T( 0 ),
        T( 0 ), T( 2 ) * n / ( t - b ), -( t + b ) / ( t - b ), T( 0 ),
        T( 0 ), T( 0 ), ( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Creates a right-handed frustum projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2n}{r-l} & 0 & \frac{r+l}{r-l} & 0 \\ 0 & \frac{2n}{t-b} & \frac{t+b}{t-b} & 0 \\ 0 & 0 & -\frac{f}{f-n} & -\frac{fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a right-handed projection matrix for use in DirectX, Vulkan, and Metal.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed frustum matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> frustumRH01( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / ( r - l ), T( 0 ), ( r + l ) / ( r - l ), T( 0 ),
        T( 0 ), T( 2 ) * n / ( t - b ), ( t + b ) / ( t - b ), T( 0 ),
        T( 0 ), T( 0 ), -f / ( f - n ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Creates a right-handed frustum projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2n}{r-l} & 0 & \frac{r+l}{r-l} & 0 \\ 0 & \frac{2n}{t-b} & \frac{t+b}{t-b} & 0 \\ 0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a right-handed projection matrix for use in OpenGL.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed frustum matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> frustumRH11( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / ( r - l ), T( 0 ), ( r + l ) / ( r - l ), T( 0 ),
        T( 0 ), T( 2 ) * n / ( t - b ), ( t + b ) / ( t - b ), T( 0 ),
        T( 0 ), T( 0 ), -( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Create a frustum projection matrix using the default configuration based on the value
/// of `FM_DEPTH_RANGE` and `FM_HANDEDNESS`
/// </summary>
/// <seealso cref="frustumLH01"/>
/// <seealso cref="frustumLH11"/>
/// <seealso cref="frustumRH01"/>
/// <seealso cref="frustumRH11"/>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A frustum projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> frustum( T l, T r, T b, T t, T n, T f ) noexcept
{
#if FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return frustumLH01( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return frustumLH11( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return frustumRH01( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return frustumRH11( l, r, b, t, n, f );
#endif
}

/// <summary>
/// Creates a left-handed orthographic projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2}{r-l} & 0 & 0 & -\frac{r+l}{r-l} \\ 0 & \frac{2}{t-b} & 0 & -\frac{t+b}{t-b} \\ 0 & 0 & \frac{1}{f-n} & -\frac{n}{f-n} \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a left-handed projection matrix for use in DirectX.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed orthographic projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> orthographicLH01( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) / ( r - l ), T( 0 ), T( 0 ), -( r + l ) / ( r - l ),
        T( 0 ), T( 2 ) / ( t - b ), T( 0 ), -( t + b ) / ( t - b ),
        T( 0 ), T( 0 ), T( 1 ) / ( f - n ), -n / ( f - n ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Creates a left-handed orthographic projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2}{r-l} & 0 & 0 & -\frac{r+l}{r-l} \\ 0 & \frac{2}{t-b} & 0 & -\frac{t+b}{t-b} \\ 0 & 0 & \frac{2}{f-n} & -\frac{f+n}{f-n} \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a left-handed projection matrix for use in OpenGL.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed orthographic projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> orthographicLH11( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) / ( r - l ), T( 0 ), T( 0 ), -( r + l ) / ( r - l ),
        T( 0 ), T( 2 ) / ( t - b ), T( 0 ), -( t + b ) / ( t - b ),
        T( 0 ), T( 0 ), T( 2 ) / ( f - n ), -( f + n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Creates a right-handed orthographic projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2}{r-l} & 0 & 0 & -\frac{r+l}{r-l} \\ 0 & \frac{2}{t-b} & 0 & -\frac{t+b}{t-b} \\ 0 & 0 & -\frac{1}{f-n} & -\frac{n}{f-n} \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a right-handed projection matrix for use in DirectX.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed orthographic projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> orthographicRH01( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) / ( r - l ), T( 0 ), T( 0 ), -( r + l ) / ( r - l ),
        T( 0 ), T( 2 ) / ( t - b ), T( 0 ), -( t + b ) / ( t - b ),
        T( 0 ), T( 0 ), T( -1 ) / ( f - n ), -n / ( f - n ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Creates a right-handed orthographic projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2}{r-l} & 0 & 0 & -\frac{r+l}{r-l} \\ 0 & \frac{2}{t-b} & 0 & -\frac{t+b}{t-b} \\ 0 & 0 & -\frac{2}{f-n} & -\frac{f+n}{f-n} \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <remarks>
/// This is commonly used to create a right-handed projection matrix for use in OpenGL.
/// </remarks>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed orthographic projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> orthographicRH11( T l, T r, T b, T t, T n, T f ) noexcept
{
    assert( std::abs( r - l ) > EPSILON<T> );
    assert( std::abs( t - b ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) / ( r - l ), T( 0 ), T( 0 ), -( r + l ) / ( r - l ),
        T( 0 ), T( 2 ) / ( t - b ), T( 0 ), -( t + b ) / ( t - b ),
        T( 0 ), T( 0 ), T( -2 ) / ( f - n ), -( f + n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Create an orthographic projection matrix using the default configuration based on the value
/// of `FM_DEPTH_RANGE` and `FM_HANDEDNESS`
/// </summary>
/// <seealso cref="orthographicLH01"/>
/// <seealso cref="orthographicLH11"/>
/// <seealso cref="orthographicRH01"/>
/// <seealso cref="orthographicRH11"/>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="l">The distance to the left clipping plane in view space.</param>
/// <param name="r">The distance to the right clipping plane in view space.</param>
/// <param name="b">The distance to the bottom clipping plane in view space.</param>
/// <param name="t">The distance to the top clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A frustum projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> orthographic( T l, T r, T b, T t, T n, T f ) noexcept
{
#if FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return orthographicLH01( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return orthographicLH11( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return orthographicRH01( l, r, b, t, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return orthographicRH11( l, r, b, t, n, f );
#endif
}

/// <summary>
/// Create a left-handed perspective projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{d}{a} & 0 & 0 & 0 \\ 0 & d & 0 & 0 \\ 0 & 0 & \frac{f}{f-n} & -\frac{fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// Where:
/// * \f(a\f) is the aspect ratio
/// * \f(d = \frac{1}{\tan(\theta_{fov}/2)}\f)
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="fovy">The vertical field of view (in radians).</param>
/// <param name="aspectRatio">The aspect ratio of the screen (\f(width/height\f)).</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveFoVLH01( T fovy, T aspectRatio, T n, T f ) noexcept
{
    assert( std::abs( aspectRatio ) > EPSILON<T> );
    assert( std::abs( fovy ) < PI<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    const T d = T( 1 ) / std::tan( fovy * T( 0.5 ) );

    return {
        d / aspectRatio, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), d, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), f / ( f - n ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Create a left-handed perspective projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{d}{a} & 0 & 0 & 0 \\ 0 & d & 0 & 0 \\ 0 & 0 & \frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// Where:
/// * \f(a\f) is the aspect ratio
/// * \f(d = \frac{1}{\tan(\theta_{fov}/2)}\f)
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="fovy">The vertical field of view (in radians).</param>
/// <param name="aspectRatio">The aspect ratio of the screen (\f(width/height\f)).</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveFoVLH11( T fovy, T aspectRatio, T n, T f ) noexcept
{
    assert( std::abs( aspectRatio ) > EPSILON<T> );
    assert( std::abs( fovy ) < PI<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    const T d = T( 1 ) / std::tan( fovy * T( 0.5 ) );

    return {
        d / aspectRatio, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), d, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), ( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Create a right-handed perspective projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{d}{a} & 0 & 0 & 0 \\ 0 & d & 0 & 0 \\ 0 & 0 & \frac{f}{n-f} & -\frac{fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// Where:
/// * \f(a\f) is the aspect ratio
/// * \f(d = \frac{1}{\tan(\theta_{fov}/2)}\f)
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="fovy">The vertical field of view (in radians).</param>
/// <param name="aspectRatio">The aspect ratio of the screen (\f(width/height\f)).</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveFoVRH01( T fovy, T aspectRatio, T n, T f ) noexcept
{
    assert( std::abs( aspectRatio ) > EPSILON<T> );
    assert( std::abs( fovy ) < PI<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    const T d = T( 1 ) / std::tan( fovy * T( 0.5 ) );

    return {
        d / aspectRatio, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), d, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), f / ( n - f ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Create a right-handed perspective projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{d}{a} & 0 & 0 & 0 \\ 0 & d & 0 & 0 \\ 0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// Where:
/// * \f(a\f) is the aspect ratio
/// * \f(d = \frac{1}{\tan(\theta_{fov}/2)}\f)
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="fovy">The vertical field of view (in radians).</param>
/// <param name="aspectRatio">The aspect ratio of the screen (\f(width/height\f)).</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveFoVRH11( T fovy, T aspectRatio, T n, T f ) noexcept
{
    assert( std::abs( aspectRatio ) > EPSILON<T> );
    assert( std::abs( fovy ) < PI<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    const T d = T( 1 ) / std::tan( fovy * T( 0.5 ) );

    return {
        d / aspectRatio, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), d, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), -( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Create a perspective projection matrix using the default configuration based on the values
/// of `FM_HANDEDNESS` and `FM_DEPTH_RANGE`.
/// </summary>
/// <seealso cref="perspectiveFoVLH01"/>
/// <seealso cref="perspectiveFoVLH11"/>
/// <seealso cref="perspectiveFoVRH01"/>
/// <seealso cref="perspectiveFoVRH11"/>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="fovy">The vertical field of view (in radians).</param>
/// <param name="aspectRatio">The aspect ratio of the screen (\f(width/height\f)).</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveFoV( T fovy, T aspectRatio, T n, T f ) noexcept
{
#if FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return perspectiveFoVLH01( fovy, aspectRatio, n, f );
#elif FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return perspectiveFoVLH11( fovy, aspectRatio, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return perspectiveFoVRH01( fovy, aspectRatio, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return perspectiveFoVRH11( fovy, aspectRatio, n, f );
#endif
}

/// <summary>
/// Create a left-handed perspective projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2n}{w} & 0 & 0 & 0 \\ 0 & \frac{2n}{h} & 0 & 0 \\ 0 & 0 & \frac{f}{f-n} & -\frac{fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="w">The frustum width at the near clipping plane in view space.</param>
/// <param name="h">The frustum height at the near clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveLH01( T w, T h, T n, T f ) noexcept
{
    assert( std::abs( w ) > EPSILON<T> );
    assert( std::abs( h ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / w, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), T( 2 ) * n / h, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), f / ( f - n ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Create a left-handed perspective projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2n}{w} & 0 & 0 & 0 \\ 0 & \frac{2n}{h} & 0 & 0 \\ 0 & 0 & \frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & 1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="w">The frustum width at the near clipping plane in view space.</param>
/// <param name="h">The frustum height at the near clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A left-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveLH11( T w, T h, T n, T f ) noexcept
{
    assert( std::abs( w ) > EPSILON<T> );
    assert( std::abs( h ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / w, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), T( 2 ) * n / h, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), ( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( 1 ), T( 0 )
    };
}

/// <summary>
/// Create a right-handed perspective projection matrix that maps depth values to the range \f([0 \ldots 1]\f).
/// \f[ \mathbf{P}_{0,1} = \begin{bmatrix}
/// \frac{2n}{w} & 0 & 0 & 0 \\ 0 & \frac{2n}{h} & 0 & 0 \\ 0 & 0 & -\frac{f}{f-n} & -\frac{fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="w">The frustum width at the near clipping plane in view space.</param>
/// <param name="h">The frustum height at the near clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveRH01( T w, T h, T n, T f ) noexcept
{
    assert( std::abs( w ) > EPSILON<T> );
    assert( std::abs( h ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / w, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), T( 2 ) * n / h, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), -f / ( f - n ), -( f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Create a right-handed perspective projection matrix that maps depth values to the range \f([-1 \ldots 1]\f).
/// \f[ \mathbf{P}_{-1,1} = \begin{bmatrix}
/// \frac{2n}{w} & 0 & 0 & 0 \\ 0 & \frac{2n}{h} & 0 & 0 \\ 0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\ 0 & 0 & -1 & 0
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="w">The frustum width at the near clipping plane in view space.</param>
/// <param name="h">The frustum height at the near clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A right-handed perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspectiveRH11( T w, T h, T n, T f ) noexcept
{
    assert( std::abs( w ) > EPSILON<T> );
    assert( std::abs( h ) > EPSILON<T> );
    assert( std::abs( f - n ) > EPSILON<T> );

    return {
        T( 2 ) * n / w, T( 0 ), T( 0 ), T( 0 ),
        T( 0 ), T( 2 ) * n / h, T( 0 ), T( 0 ),
        T( 0 ), T( 0 ), -( f + n ) / ( f - n ), -( T( 2 ) * f * n ) / ( f - n ),
        T( 0 ), T( 0 ), T( -1 ), T( 0 )
    };
}

/// <summary>
/// Create a perspective projection matrix using the default configuration based on the values
/// of `FM_HANDEDNESS` and `FM_DEPTH_RANGE`.
/// </summary>
/// <seealso cref="perspectiveLH01"/>
/// <seealso cref="perspectiveLH11"/>
/// <seealso cref="perspectiveRH01"/>
/// <seealso cref="perspectiveRH11"/>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="w">The width of the frustum at the near clipping plane in view space.</param>
/// <param name="h">The height of the frustum at the near clipping plane in view space.</param>
/// <param name="n">The distance to the near clipping plane in view space.</param>
/// <param name="f">The distance to the far clipping plane in view space.</param>
/// <returns>A perspective projection matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> perspective( T w, T h, T n, T f ) noexcept
{
#if FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return perspectiveLH01( w, h, n, f );
#elif FM_HANDEDNESS == FM_LEFT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return perspectiveLH11( w, h, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_ZERO_TO_ONE
    return perspectiveRH01( w, h, n, f );
#elif FM_HANDEDNESS == FM_RIGHT_HANDED && FM_DEPTH_RANGE == FM_NEGATIVE_ONE_TO_ONE
    return perspectiveRH11( w, h, n, f );
#endif
}

/// <summary>
/// Build a left-handed view matrix.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="target">The target to look at.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A left-handed view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookAtLH( const Vector<T, 3>& eye, const Vector<T, 3>& target, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
    const Vector<T, 3> Z( normalize( target - eye ) );
    const Vector<T, 3> X( normalize( cross( up, Z ) ) );
    const Vector<T, 3> Y( cross( Z, X ) );

    return {
        X.x, X.y, X.z, -dot( X, eye ),
        Y.x, Y.y, Y.z, -dot( Y, eye ),
        Z.x, Z.y, Z.z, -dot( Z, eye ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Build a right-handed view matrix.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="target">The target to look at.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A right-handed view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookAtRH( const Vector<T, 3>& eye, const Vector<T, 3>& target, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
    const Vector<T, 3> Z( normalize( eye - target ) );
    const Vector<T, 3> X( normalize( cross( up, Z ) ) );
    const Vector<T, 3> Y( cross( Z, X ) );

    return {
        X.x, X.y, X.z, -dot( X, eye ),
        Y.x, Y.y, Y.z, -dot( Y, eye ),
        Z.x, Z.y, Z.z, -dot( Z, eye ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Build a view matrix depending on the value of `FM_HANDEDNESS`.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="target">The target to look at.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookAt( const Vector<T, 3>& eye, const Vector<T, 3>& target, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
#if FM_HANDEDNESS == FM_LEFT_HANDED
    return lookAtLH( eye, target, up );
#else
    return lookAtRH( eye, target, up );
#endif
}

/// <summary>
/// Build a left-handed view matrix based on the eye position and a look-towards direction.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="direction">The direction the camera is looking.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A left-handed view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookToLH( const Vector<T, 3>& eye, const Vector<T, 3>& direction, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
    const Vector<T, 3> Z( normalize( direction ) );
    const Vector<T, 3> X( normalize( cross( up, Z ) ) );
    const Vector<T, 3> Y( cross( Z, X ) );

    return {
        X.x, X.y, X.z, -dot( X, eye ),
        Y.x, Y.y, Y.z, -dot( Y, eye ),
        Z.x, Z.y, Z.z, -dot( Z, eye ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Build a right-handed view matrix based on the eye position and a look-towards direction.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="direction">The direction the camera is looking.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A right-handed view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookToRH( const Vector<T, 3>& eye, const Vector<T, 3>& direction, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
    const Vector<T, 3> Z( normalize( -direction ) );
    const Vector<T, 3> X( normalize( cross( up, Z ) ) );
    const Vector<T, 3> Y( cross( Z, X ) );

    return {
        X.x, X.y, X.z, -dot( X, eye ),
        Y.x, Y.y, Y.z, -dot( Y, eye ),
        Z.x, Z.y, Z.z, -dot( Z, eye ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

/// <summary>
/// Build a look-to view matrix based on the value of `FM_HANDEDNESS`.
/// </summary>
/// <typeparam name="T">The matrix type.</typeparam>
/// <param name="eye">The eye position.</param>
/// <param name="direction">The direction the camera is looking.</param>
/// <param name="up">(optional) The up vector (usually {0, 1, 0}).</param>
/// <returns>A look-to view matrix.</returns>
template<typename T>
constexpr Matrix<T, 4, 4> lookTo( const Vector<T, 3>& eye, const Vector<T, 3>& direction, const Vector<T, 3>& up = Vector<T, 3>::UNIT_Y )
{
#if FM_HANDEDNESS == FM_LEFT_HANDED
    return lookToLH( eye, direction, up );
#else
    return lookToRH( eye, direction, up );
#endif
}

}  // namespace FastMath
