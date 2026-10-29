#pragma once

#include "Common.hpp"
#include "Concepts.hpp"
#include "VectorBase.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <span>
#include <type_traits>

namespace FastMath
{

template<typename T, std::size_t N>
struct Vector : VectorBase<T, N>
{
    /// <summary>
    /// The type of this Vector.
    /// </summary>
    using type = Vector<T, N>;

    /// <summary>
    /// The Vector value type.
    /// </summary>
    using value_type = T;

    /// <summary>
    /// The Vector size type.
    /// </summary>
    using size_type = std::size_t;

    /// <summary>
    /// The rank of the Vector. This is just the number of components of the Vector.
    /// </summary>
    static constexpr std::size_t rank = N;

    /// <summary>
    /// Zero Vector (all components are zero).
    /// </summary>
    static const Vector<T, N> ZERO;

    /// <summary>
    /// Unit X Vector (the x-component is 1, all other components are 0).
    /// </summary>
    static const Vector<T, N> UNIT_X;

    /// <summary>
    /// Unit Y Vector (the y-component is 1, all other components are 0).
    /// </summary>
    static const Vector<T, N> UNIT_Y;

    /// <summary>
    /// Unit Z Vector (the z-component is 1, all other components are 0).
    /// </summary>
    static const Vector<T, N> UNIT_Z;

    /// <summary>
    /// Unit W Vector (the w-component is 1, all other components are 0).
    /// </summary>
    static const Vector<T, N> UNIT_W;

    /// <summary>
    /// Return the number of components of this Vector.
    /// </summary>
    /// <remarks>
    /// For compatibility with `std::size()`.
    /// </remarks>
    /// <returns>The number of components of this Vector.</returns>
    static constexpr std::size_t size() noexcept;

    /// <summary>
    /// Get a pointer to the first component of the Vector.
    /// </summary>
    /// <remarks>
    /// For compatibility with `std::data()`.
    /// </remarks>
    /// <returns>A pointer to the first element of the Vector.</returns>
    constexpr T* data() noexcept;

    /// <summary>
    /// Get a const pointer to the first component of the Vector.
    /// </summary>
    /// <remarks>
    /// For compatibility with `std::data()`.
    /// </remarks>
    /// <returns>A pointer to the first element of the Vector.</returns>
    constexpr const T* data() const noexcept;

    /// <summary>
    /// Vector base class.
    /// </summary>
    using base = VectorBase<T, N>;

    /// <summary>
    /// Default constructor for a Vector. All components are set to 0.
    /// </summary>
    constexpr Vector() noexcept;

    /// <summary>
    /// Construct a Vector by setting all components to a scalar value.
    /// </summary>
    /// <remarks>
    /// To ensure the compiler chooses this constructor over the one that takes an
    /// initializer list, the vector must be constructed like this:
    /// <code>
    /// Vector4f a( x );        // Do not use direct-list-initialization.
    /// auto a = Vector4f( x ); // Do not use copy-list-initialization.
    /// </code>
    /// See <a href="https://en.cppreference.com/w/cpp/utility/initializer_list">`std::initializer_list`</a> for more information
    /// about initializer lists and when an `std::initializer_list` is used.
    /// </remarks>
    /// <param name="s">The scalar to copy to all components of the Vector.</param>
    template<ConvertibleTo<T> X>
    explicit constexpr Vector( X s ) noexcept;

    /// <summary>
    /// Construct a vector by setting the first two components.
    /// </summary>
    /// <remarks>
    /// Any unspecified components are initialized to 0.
    /// </remarks>
    /// <param name="x">The x component.</param>
    /// <param name="y">The y component.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y>
    constexpr Vector( X x, Y y ) noexcept;

    /// <summary>
    /// Construct a vector by setting the first two components.
    /// </summary>
    /// <remarks>
    /// Any unspecified components are initialized to 0.
    /// </remarks>
    /// <param name="x">The x component.</param>
    /// <param name="y">The y component.</param>
    /// <param name="z">The z component.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z>
    constexpr Vector( X x, Y y, Z z ) noexcept;

    /// <summary>
    /// Construct a vector by setting the first two components.
    /// </summary>
    /// <remarks>
    /// Any unspecified components are initialized to 0.
    /// </remarks>
    /// <param name="x">The x component.</param>
    /// <param name="y">The y component.</param>
    /// <param name="z">The z component.</param>
    /// <param name="w">The w component.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> W>
    constexpr Vector( X x, Y y, Z z, W w ) noexcept;

    /// <summary>
    /// Construct a Vector from a span. This allows the Vector to be constructed
    /// from `std::vector` and arrays:
    /// <code>
    /// float a[] = { 1, 2, 3, 4 };
    /// Vector4f v = std::span{ a };
    /// </code>
    /// </summary>
    /// <param name="s">The std::span to use to construct this Vector.</param>
    template<ConvertibleTo<T> U, std::size_t M>
    constexpr Vector( std::span<U, M> s ) noexcept;

    /// <summary>
    /// Copy another Vector to this one.
    /// This allows for vectors of different sizes to be copied.
    /// <code>
    /// Vector2f a{ 1, 2 };
    /// Vector4f b{ a, 3, 4 };
    /// </code>
    /// </summary>
    /// <param name="copy">The Vector to copy to this one.</param>
    /// <param name="args">Any number of additional parameters to fill this Vector.</param>
    template<ConvertibleTo<T> U, std::size_t M, ConvertibleTo<T>... Args>
    constexpr Vector( const Vector<U, M>& copy, const Args&... args ) noexcept;

    /// <summary>
    /// Copy another Vector to this one.
    /// This allows for Vectors of different sizes to be copied.
    /// <code>
    /// Vector2f a{ 2, 3 };
    /// Vector3f b{ 1, a };
    /// </code>
    /// </summary>
    /// <param name="x">The x-component.</param>
    /// <param name="copy">The rest of the components are filled from this Vector.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> U, std::size_t M>
    constexpr Vector( X x, const Vector<U, M>& copy );

    /// <summary>
    /// Copy another Vector to this one.
    /// This allows for Vectors of different sizes to be copied.
    /// <code>
    /// Vector2f a{ 3, 4 };
    /// Vector4f b{ 1, 2, a };
    /// </code>
    /// </summary>
    /// <param name="x">The x-component.</param>
    /// <param name="y">The y-component.</param>
    /// <param name="copy">The rest of the components are filled from this Vector.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> U, std::size_t M>
    constexpr Vector( X x, Y y, const Vector<U, M>& copy );

    /// <summary>
    /// Copy another vector to this one.
    /// This allows for vectors of different sizes to be copied.
    /// <code>
    /// Vector2f a{ 4, 5 };
    /// Vector4f b{ 1, 2, 3, a }; // The last component is not copied to b.
    /// </code>
    /// </summary>
    /// <param name="x">The x-component.</param>
    /// <param name="y">The y-component.</param>
    /// <param name="z">The z-component.</param>
    /// <param name="copy">The rest of teh components are filled from this vector.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> U, std::size_t M>
    constexpr Vector( X x, Y y, Z z, const Vector<U, M>& copy );

    /// <summary>
    /// Copy another vector to this one.
    /// This allows for vectors of different sizes to be copied.
    /// <code>
    /// Vector2f a{ 4, 5 };
    /// Vector4f b{ 1, 2, 3, 4, a }; // The last components are not copied to b.
    /// </summary>
    /// <param name="x">The x-component.</param>
    /// <param name="y">The y-component.</param>
    /// <param name="z">The z-component.</param>
    /// <param name="w">The w-component.</param>
    /// <param name="copy">The rest of the components are filled from this vector.</param>
    template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> W, ConvertibleTo<T> U, std::size_t M>
    constexpr Vector( X x, Y y, Z z, W w, const Vector<U, M>& copy );

    /// <summary>
    /// Copy another vector to this one.
    /// </summary>
    /// <remarks>
    /// Vectors of different sizes can be assigned to this one.
    /// If the `rhs` is larger than this vector, only the first `N` components
    /// are copied.
    /// If the `rhs` is smaller than this vector, the remaining components are
    /// filled with 0's.
    /// </remarks>
    /// <param name="rhs">The vector to copy to this one.</param>
    /// <returns>A reference to this vector after assignment.</returns>
    template<ConvertibleTo<T> U, std::size_t M>
    constexpr Vector<T, N>& operator=( const Vector<U, M>& rhs ) noexcept;

    /// <summary>
    /// Get the component at index i.
    /// </summary>
    /// <remarks>
    /// `i` must be less than the number of components of the vector (this is asserted in debug builds).
    /// The operator is defined in VectorBase, which owns the components.
    /// </remarks>
    using base::operator[];

    /// <summary>
    /// Unary plus operator.
    /// </summary>
    /// <returns>A copy of this vector.</returns>
    constexpr Vector<T, N> operator+() const noexcept;

    /// <summary>
    /// Unary minus operator.
    /// </summary>
    /// <returns>A negated copy of this vector.</returns>
    constexpr Vector<T, N> operator-() const noexcept
        requires IsSigned<T>;

    /// <summary>
    /// Add and assignment operator.
    /// </summary>
    /// <param name="rhs">The vector to add to this one.</param>
    /// <returns>A reference to this vector after summing.</returns>
    constexpr Vector<T, N>& operator+=( const Vector<T, N>& rhs ) noexcept;

    /// <summary>
    /// Subtract and assignment operator.
    /// </summary>
    /// <param name="rhs">The vector to subtract from this one.</param>
    /// <returns>A reference to this vector after subtraction.</returns>
    constexpr Vector<T, N>& operator-=( const Vector<T, N>& rhs ) noexcept;

    /// <summary>
    /// Component-wise multiplication and assignment.
    /// </summary>
    /// <param name="rhs">The vector to multiply with this one.</param>
    /// <returns>A reference to this vector after component-wise multiplication.</returns>
    constexpr Vector<T, N>& operator*=( const Vector<T, N>& rhs ) noexcept;

    /// <summary>
    /// Scalar multiplication and assignment.
    /// </summary>
    /// <param name="s">The scalar to multiply with this vector.</param>
    /// <returns>A reference to this vector after scalar multiplication.</returns>
    constexpr Vector<T, N>& operator*=( T s ) noexcept;

    /// <summary>
    /// Scalar division and assignment.
    /// </summary>
    /// <remarks>
    /// It is the responsibility of the user to ensure `s` is not 0.
    /// </remarks>
    /// <param name="s">The scalar to divide.</param>
    /// <returns>A reference to this vector after scalar division.</returns>
    constexpr Vector<T, N>& operator/=( T s ) noexcept;

    // The binary operators are hidden friends: they are only found by argument-dependent lookup
    // when one of the operands is a Vector<T, N>. This keeps overload resolution (and compile errors)
    // small, and allows the scalar to be on either side of the operator.
    //
    // They build the result directly instead of copying an operand and using the compound operator
    // (`lhs += rhs`): MSVC copies the members of a by-value vector one at a time, which prevents it
    // from using a single SIMD load.

    /// <summary>
    /// Vector addition.
    /// </summary>
    /// <param name="lhs">The first vector.</param>
    /// <param name="rhs">The second vector.</param>
    /// <returns>The component-wise sum of `lhs` and `rhs`.</returns>
    friend constexpr Vector<T, N> operator+( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = lhs[i] + rhs[i];

        return res;
    }

    /// <summary>
    /// Vector difference.
    /// </summary>
    /// <param name="lhs">The first vector.</param>
    /// <param name="rhs">The vector to subtract from `lhs`.</param>
    /// <returns>The result of subtracting `rhs` from `lhs`.</returns>
    friend constexpr Vector<T, N> operator-( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = lhs[i] - rhs[i];

        return res;
    }

    /// <summary>
    /// Component-wise multiplication.
    /// </summary>
    /// <param name="lhs">The first vector.</param>
    /// <param name="rhs">The second vector.</param>
    /// <returns>The component-wise product of `lhs` and `rhs`.</returns>
    friend constexpr Vector<T, N> operator*( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = lhs[i] * rhs[i];

        return res;
    }

    /// <summary>
    /// Scalar multiplication.
    /// </summary>
    /// <param name="lhs">The vector.</param>
    /// <param name="s">The scalar to multiply with the vector.</param>
    /// <returns>The result of multiplying each component of `lhs` by `s`.</returns>
    friend constexpr Vector<T, N> operator*( const Vector<T, N>& lhs, T s ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = lhs[i] * s;

        return res;
    }

    /// <summary>
    /// Scalar multiplication.
    /// </summary>
    /// <param name="s">The scalar to multiply with the vector.</param>
    /// <param name="rhs">The vector.</param>
    /// <returns>The result of multiplying each component of `rhs` by `s`.</returns>
    friend constexpr Vector<T, N> operator*( T s, const Vector<T, N>& rhs ) noexcept
    {
        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = s * rhs[i];

        return res;
    }

    /// <summary>
    /// Scalar division.
    /// </summary>
    /// <remarks>
    /// It is the responsibility of the user to ensure `s` is not 0.
    /// </remarks>
    /// <param name="lhs">The vector.</param>
    /// <param name="s">The scalar to divide.</param>
    /// <returns>The result of dividing each component of `lhs` by `s`.</returns>
    friend constexpr Vector<T, N> operator/( const Vector<T, N>& lhs, T s ) noexcept
    {
        assert( s != T( 0 ) );

        Vector<T, N> res;

        for ( std::size_t i = 0; i < N; ++i )
            res[i] = lhs[i] / s;

        return res;
    }

    /// <summary>
    /// Three-way comparison operator.
    /// Allows for all other comparison operators.
    /// </summary>
    /// <param name="lhs">The first vector to compare.</param>
    /// <param name="rhs">The second vector to compare.</param>
    /// <returns>Comparison category type (boolean if using any of the standard comparison operators).</returns>
    friend constexpr auto operator<=>( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
    {
        auto res = lhs[0] <=> rhs[0];

        for ( std::size_t i = 1; i < N && res == 0; ++i )
            res = lhs[i] <=> rhs[i];

        return res;
    }

    /// <summary>
    /// Equality comparison operator.
    /// </summary>
    /// <remarks>
    /// This performs equality comparison on floating-point values (which is usually not reliable).
    /// If you need to check if two vectors are nearly equal, use <see cref="FastMath::equal"/>
    /// </remarks>
    /// <param name="lhs">The first vector to compare.</param>
    /// <param name="rhs">The second vector to compare.</param>
    /// <returns>`true` if all of the components are equal, `false` otherwise.</returns>
    friend constexpr bool operator==( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
    {
        for ( std::size_t i = 0; i < N; ++i )
            if ( lhs[i] != rhs[i] )
                return false;

        return true;
    }
};

using Vector2f = Vector<float, 2>;
using Vector2d = Vector<double, 2>;
using Vector2i = Vector<int32_t, 2>;
using Vector2u = Vector<uint32_t, 2>;

using Vector3f = Vector<float, 3>;
using Vector3d = Vector<double, 3>;
using Vector3i = Vector<int32_t, 3>;
using Vector3u = Vector<uint32_t, 3>;

using Vector4f = Vector<float, 4>;
using Vector4d = Vector<double, 4>;
using Vector4i = Vector<int32_t, 4>;
using Vector4u = Vector<uint32_t, 4>;

using float2 = Vector<float, 2>;
using float3 = Vector<float, 3>;
using float4 = Vector<float, 4>;

using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;

using dvec2 = Vector<double, 2>;
using dvec3 = Vector<double, 3>;
using dvec4 = Vector<double, 4>;

using double2 = Vector<double, 2>;
using double3 = Vector<double, 3>;
using double4 = Vector<double, 4>;

using int2 = Vector<int32_t, 2>;
using int3 = Vector<int32_t, 3>;
using int4 = Vector<int32_t, 4>;

using uint2 = Vector<uint32_t, 2>;
using uint3 = Vector<uint32_t, 3>;
using uint4 = Vector<uint32_t, 4>;

using usize2 = Vector<size_t, 2>;
using usize3 = Vector<size_t, 3>;
using usize4 = Vector<size_t, 4>;

template<typename T, std::size_t N>
constexpr std::size_t Vector<T, N>::size() noexcept
{
    return N;
}

template<typename T, std::size_t N>
constexpr T* Vector<T, N>::data() noexcept
{
    static_assert( sizeof( Vector<T, N> ) == N * sizeof( T ), "The components must be tightly packed." );
    return &( *this )[0];
}

template<typename T, std::size_t N>
constexpr const T* Vector<T, N>::data() const noexcept
{
    static_assert( sizeof( Vector<T, N> ) == N * sizeof( T ), "The components must be tightly packed." );
    return &( *this )[0];
}

template<typename T, std::size_t N>
constexpr Vector<T, N>::Vector() noexcept = default;

template<typename T, std::size_t N>
template<ConvertibleTo<T> X>
constexpr Vector<T, N>::Vector( X s ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] = static_cast<T>( s );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y>
constexpr Vector<T, N>::Vector( X x, Y y ) noexcept
{
    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z>
constexpr Vector<T, N>::Vector( X x, Y y, Z z ) noexcept
{
    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );

    if constexpr ( N > 2 )
        ( *this )[2] = static_cast<T>( z );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> W>
constexpr Vector<T, N>::Vector( X x, Y y, Z z, W w ) noexcept
{
    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );

    if constexpr ( N > 2 )
        ( *this )[2] = static_cast<T>( z );

    if constexpr ( N > 3 )
        ( *this )[3] = static_cast<T>( w );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>::Vector( std::span<U, M> s ) noexcept
{
    const std::size_t c = std::min( N, s.size() );

    for ( std::size_t i = 0; i < c; ++i )
        ( *this )[i] = static_cast<T>( s[i] );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> U, std::size_t M, ConvertibleTo<T>... Args>
constexpr Vector<T, N>::Vector( const Vector<U, M>& copy, const Args&... args ) noexcept
{
    constexpr std::size_t c = std::min( N, M );

    std::size_t i = 0;
    for ( ; i < c; ++i )
        ( *this )[i] = static_cast<T>( copy[i] );

    // Unfold any additional arguments.
    ( ( ( i < N ) ? ( *this )[i++] = static_cast<T>( args ) : false ), ... );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>::Vector( X x, const Vector<U, M>& copy )
{
    constexpr std::size_t c = std::min( N, M + 1 );

    ( *this )[0] = static_cast<T>( x );

    for ( std::size_t i = 1; i < c; ++i )
        ( *this )[i] = static_cast<T>( copy[i - 1] );
}
template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>::Vector( X x, Y y, const Vector<U, M>& copy )
{
    constexpr std::size_t c = std::min( N, M + 2 );

    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );

    for ( std::size_t i = 2; i < c; ++i )
        ( *this )[i] = static_cast<T>( copy[i - 2] );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>::Vector( X x, Y y, Z z, const Vector<U, M>& copy )
{
    constexpr std::size_t c = std::min( N, M + 3 );

    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );

    if constexpr ( N > 2 )
        ( *this )[2] = static_cast<T>( z );

    for ( std::size_t i = 3; i < c; ++i )
        ( *this )[i] = static_cast<T>( copy[i - 3] );
}

template<typename T, std::size_t N>
template<ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z, ConvertibleTo<T> W, ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>::Vector( X x, Y y, Z z, W w, const Vector<U, M>& copy )
{
    constexpr std::size_t c = std::min( N, M + 4 );

    ( *this )[0] = static_cast<T>( x );

    if constexpr ( N > 1 )
        ( *this )[1] = static_cast<T>( y );

    if constexpr ( N > 2 )
        ( *this )[2] = static_cast<T>( z );

    if constexpr ( N > 3 )
        ( *this )[3] = static_cast<T>( w );

    for ( std::size_t i = 4; i < c; ++i )
        ( *this )[i] = static_cast<T>( copy[i - 4] );
}

// The constants are defined after the constructors so they can be evaluated at compile time.
template<typename T, std::size_t N>
inline constexpr Vector<T, N> Vector<T, N>::ZERO { 0 };

template<typename T, std::size_t N>
inline constexpr Vector<T, N> Vector<T, N>::UNIT_X { T( 1 ), T( 0 ) };

template<typename T, std::size_t N>
inline constexpr Vector<T, N> Vector<T, N>::UNIT_Y { T( 0 ), T( 1 ) };

template<typename T, std::size_t N>
inline constexpr Vector<T, N> Vector<T, N>::UNIT_Z { T( 0 ), T( 0 ), T( 1 ) };

template<typename T, std::size_t N>
inline constexpr Vector<T, N> Vector<T, N>::UNIT_W { T( 0 ), T( 0 ), T( 0 ), T( 1 ) };

template<typename T, std::size_t N>
template<ConvertibleTo<T> U, std::size_t M>
constexpr Vector<T, N>& Vector<T, N>::operator=( const Vector<U, M>& rhs ) noexcept
{
    constexpr std::size_t c = std::min( N, M );

    for ( std::size_t i = 0; i < c; ++i )
        ( *this )[i] = static_cast<T>( rhs[i] );

    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator+() const noexcept
{
    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-() const noexcept
    requires IsSigned<T>
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = -( *this )[i];

    return res;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator+=( const Vector<T, N>& rhs ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] += rhs[i];

    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator-=( const Vector<T, N>& rhs ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] -= rhs[i];

    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=( const Vector<T, N>& rhs ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] *= rhs[i];

    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=( T s ) noexcept
{
    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] *= s;

    return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator/=( T s ) noexcept
{
    assert( s != T( 0 ) );

    for ( std::size_t i = 0; i < N; ++i )
        ( *this )[i] /= s;

    return *this;
}

/// <summary>
/// Compute the cross product two vectors.
/// </summary>
/// <remarks>
/// The cross product is only defined for 3-component vectors.
/// </remarks>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="lhs">The first vector.</param>
/// <param name="rhs">The second vector.</param>
/// <returns>The result of the cross product.</returns>
template<typename T>
constexpr Vector<T, 3> cross( const Vector<T, 3>& lhs, const Vector<T, 3>& rhs ) noexcept
{
    return { lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
}

#if defined( FM_SSE )
namespace detail
{
/// <summary>
/// SIMD implementation of the dot product for 4-component floating-point vectors.
/// </summary>
inline float dot( const Vector<float, 4>& v1, const Vector<float, 4>& v2 ) noexcept
{
    // This is faster than _mm_dp_ps (SSE4) and _mm_hadd_ps (SSE3) on modern CPUs, and only needs SSE.
    const __m128 a  = _mm_load_ps( &v1.x );
    const __m128 b  = _mm_load_ps( &v2.x );
    const __m128 m  = _mm_mul_ps( a, b );                                        // (xx, yy, zz, ww)
    const __m128 s1 = _mm_add_ps( m, _mm_shuffle_ps( m, m, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );  // (xx+yy, xx+yy, zz+ww, zz+ww)
    const __m128 s2 = _mm_add_ss( s1, _mm_movehl_ps( s1, s1 ) );                 // (xx+yy+zz+ww, ...)

    return _mm_cvtss_f32( s2 );
}
}  // namespace detail
#endif

/// <summary>
/// Compute the dot product between two vectors.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="lhs">The first vector.</param>
/// <param name="rhs">The second vector.</param>
/// <returns>The result of the dot product.</returns>
template<typename T, std::size_t N>
constexpr T dot( const Vector<T, N>& lhs, const Vector<T, N>& rhs ) noexcept
{
#if defined( FM_SSE )
    if constexpr ( std::is_same_v<T, float> && N == 4 )
    {
        if ( !std::is_constant_evaluated() )
            return detail::dot( lhs, rhs );
    }
#endif

    T res = T( 0 );

    for ( std::size_t i = 0; i < N; ++i )
        res += lhs[i] * rhs[i];

    return res;
}

/// <summary>
/// Compute the squared length of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector.</param>
/// <returns>The squared length of `v`.</returns>
template<typename T, std::size_t N>
constexpr T lengthSqr( const Vector<T, N>& v ) noexcept
{
    return dot( v, v );
}

/// <summary>
/// Compute the length of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector.</param>
/// <returns>The length of `v`.</returns>
template<typename T, std::size_t N>
constexpr T length( const Vector<T, N>& v ) noexcept
{
    return std::sqrt( lengthSqr( v ) );
}

/// <summary>
/// Vector normalization.
/// </summary>
/// <remarks>
/// If the vector has a length of 0, the vector is returned unchanged.
/// </remarks>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to normalize.</param>
/// <returns>The normalized vector.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> normalize( const Vector<T, N>& v ) noexcept
{
    const T l = length( v );

    if ( l > T( 0 ) )
        return v / l;

    return v;
}

/// <summary>
/// Check to see if a vector is normalized.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to check.</param>
/// <param name="epsilon">(optional) The error tolerance.</param>
/// <returns>`true` if the length of the vector is within the error tolerance.</returns>
template<typename T, std::size_t N>
constexpr bool isNormalized( const Vector<T, N>& v, T epsilon = EPSILON<T> ) noexcept
{
    return ( std::abs( T( 1 ) - lengthSqr( v ) ) < epsilon );
}

/// <summary>
/// The component-wise absolute value of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to take the absolute value of.</param>
/// <returns>The component-wise absolute value of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> abs( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::abs( v[i] );

    return res;
}

/// <summary>
/// Component-wise less than operator.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="a">The first vector to compare.</param>
/// <param name="b">The second vector to compare.</param>
/// <returns>The component-wise result of comparing `a[i] < b[i]`.</returns>
template<typename T, std::size_t N>
constexpr Vector<bool, N> lessThan( const Vector<T, N>& a, const Vector<T, N>& b ) noexcept
{
    Vector<bool, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = a[i] < b[i];

    return res;
}

/// <summary>
/// Component-wise less than or equal operator.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="a">The first vector to compare.</param>
/// <param name="b">The second vector to compare.</param>
/// <returns>The component-wise result of comparing `a[i] <= b[i]`.</returns>
template<typename T, std::size_t N>
constexpr Vector<bool, N> lessThanEqual( const Vector<T, N>& a, const Vector<T, N>& b ) noexcept
{
    Vector<bool, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = a[i] <= b[i];

    return res;
}

/// <summary>
/// Component-wise greater than operator.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="a">The first vector to compare.</param>
/// <param name="b">The second vector to compare.</param>
/// <returns>The component-wise result of comparing `a[i] > b[i]`.</returns>
template<typename T, std::size_t N>
constexpr Vector<bool, N> greaterThan( const Vector<T, N>& a, const Vector<T, N>& b ) noexcept
{
    Vector<bool, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = a[i] > b[i];

    return res;
}

/// <summary>
/// Component-wise greater than or equal operator.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="a">The first vector to compare.</param>
/// <param name="b">The second vector to compare.</param>
/// <returns>The component-wise result of comparing `a[i] >= b[i]`.</returns>
template<typename T, std::size_t N>
constexpr Vector<bool, N> greaterThanEqual( const Vector<T, N>& a, const Vector<T, N>& b ) noexcept
{
    Vector<bool, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = a[i] >= b[i];

    return res;
}

/// <summary>
/// Check if any of the components of the boolean vector are true.
/// </summary>
/// <param name="v">The boolean vector to check.</param>
/// <returns>`true` if any of the components are true, `false` otherwise.</returns>
template<std::size_t N>
constexpr bool any( const Vector<bool, N>& v ) noexcept
{
    bool res = false;

    for ( std::size_t i = 0; i < N && !res; ++i )
        res = res || v[i];

    return res;
}

/// <summary>
/// Check if all of the components of a boolean vector are true.
/// </summary>
/// <param name="v">The boolean vector to check.</param>
/// <returns>`true` if all of the components are true, `false` otherwise.</returns>
template<std::size_t N>
constexpr bool all( const Vector<bool, N>& v ) noexcept
{
    bool res = true;

    for ( std::size_t i = 0; i < N && res; ++i )
        res = res && v[i];

    return res;
}

/// <summary>
/// Negate the boolean vector.
/// </summary>
/// <param name="v">The boolean vector to negate.</param>
/// <returns>The result of negating each component of the boolean vector.</returns>
template<std::size_t N>
constexpr Vector<bool, N> negate( const Vector<bool, N>& v ) noexcept
{
    Vector<bool, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = !v[i];

    return res;
}

template<typename T, std::size_t N>
constexpr Vector<bool, N> equal( const Vector<T, N>& a, const Vector<T, N>& b, const Vector<T, N>& epsilon = Vector<T, N>::ZERO ) noexcept
{
    return lessThanEqual( abs( a - b ), epsilon );
}

template<typename T, std::size_t N, ConvertibleTo<T> U = T>
constexpr Vector<bool, N> equal( const Vector<T, N>& a, const Vector<T, N>& b, U epsilon ) noexcept
{
    return equal( a, b, Vector<U, N>( epsilon ) );
}

template<typename T, std::size_t N>
constexpr Vector<bool, N> notEqual( const Vector<T, N>& a, const Vector<T, N>& b, const Vector<T, N>& epsilon = Vector<T, N>::ZERO ) noexcept
{
    return negate( equal( a, b, epsilon ) );
}

template<typename T, std::size_t N>
constexpr Vector<bool, N> notEqual( const Vector<T, N>& a, const Vector<T, N>& b, T epsilon ) noexcept
{
    return negate( equal( a, b, epsilon ) );
}

/// <summary>
/// Convert a vector of radian values to degrees.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector of radians.</param>
/// <returns>The vector of degrees.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> degrees( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = degrees( v[i] );

    return res;
}

/// <summary>
/// Convert a vector of degree values to radians.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector of degrees.</param>
/// <returns>The vector of radians.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> radians( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = radians( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise cosine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `cos` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> cos( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::cos( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise sine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `sin` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> sin( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::sin( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise tangent of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `tan` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> tan( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::tan( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise arc sine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `asin` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> asin( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::asin( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise arc cosine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `acos` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> acos( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::acos( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise arc tangent of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `atan` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> atan( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::atan( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise hyperbolic sine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `sinh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> sinh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::sinh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise hyperbolic cosine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `cosh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> cosh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::cosh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise hyperbolic tangent of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `tanh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> tanh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::tanh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise inverse hyperbolic sine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `asinh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> asinh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::asinh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise inverse hyperbolic cosine of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `acosh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> acosh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::acosh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise inverse hyperbolic tangent of a vector.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The input vector.</param>
/// <returns>The component-wise `atanh` of `v`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> atanh( const Vector<T, N>& v ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::atanh( v[i] );

    return res;
}

/// <summary>
/// Compute the component-wise arc tangent of `y / x` using the signs of the arguments to determine the correct quadrant.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="y">The vector of y values.</param>
/// <param name="x">The vector of x values.</param>
/// <returns>The component-wise `atan2` of `y` and `x`.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, N> atan2( const Vector<T, N>& y, const Vector<T, N>& x ) noexcept
{
    Vector<T, N> res;

    for ( std::size_t i = 0; i < N; ++i )
        res[i] = std::atan2( y[i], x[i] );

    return res;
}

/// <summary>
/// Swizzle a single component from v.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to extract the component.</param>
/// <param name="X">The component to extract.</param>
/// <returns>The component of `v` at index `X`.</returns>
template<typename T, std::size_t N>
constexpr T swizzle( const Vector<T, N>& v, std::size_t X ) noexcept
{
    assert( X < N );
    return v[X];
}

/// <summary>
/// Swizzle two components from v.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to extract the components.</param>
/// <param name="X">The first component to extract.</param>
/// <param name="Y">The second component to extract.</param>
/// <returns>The result of swizzling `v` with the X, and Y components.</returns>
template<typename T, std::size_t N>
constexpr Vector<T, 2> swizzle( const Vector<T, N>& v, std::size_t X, std::size_t Y ) noexcept
{
    assert( X < N );
    assert( Y < N );

    return { v[X], v[Y] };
}

/// <summary>
/// Swizzle three components from v.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to extract the components.</param>
/// <param name="X">The first component to extract.</param>
/// <param name="Y">The second component to extract.</param>
/// <param name="Z">The third component to extract.</param>
/// <returns></returns>
template<typename T, std::size_t N>
constexpr Vector<T, 3> swizzle( const Vector<T, N>& v, std::size_t X, std::size_t Y, std::size_t Z ) noexcept
{
    assert( X < N );
    assert( Y < N );
    assert( Z < N );

    return { v[X], v[Y], v[Z] };
}

/// <summary>
/// Swizzle four components from v.
/// </summary>
/// <typeparam name="T">The vector type.</typeparam>
/// <param name="v">The vector to extract the components.</param>
/// <param name="X">The first component to extract.</param>
/// <param name="Y">The second component to extract.</param>
/// <param name="Z">The third component to extract.</param>
/// <param name="W">The fourth component to extract.</param>
/// <returns></returns>
template<typename T, std::size_t N>
constexpr Vector<T, 4> swizzle( const Vector<T, N>& v, std::size_t X, std::size_t Y, std::size_t Z, std::size_t W ) noexcept
{
    assert( X < N );
    assert( Y < N );
    assert( Z < N );
    assert( W < N );

    return { v[X], v[Y], v[Z], v[W] };
}

}  // namespace FastMath
