#pragma once

#include "Common.hpp"
#include "Concepts.hpp"
#include "Matrix.hpp"
#include "QuaternionBase.hpp"
#include "Vector.hpp"

#include <cstddef>

namespace FastMath
{
template<typename T>
struct Quaternion : QuaternionBase<T>
{
    using value_type = T;
    using base       = QuaternionBase<T>;

    /// <summary>
    /// Quaternion identity. This is equivalent to an identity matrix (no rotation).
    /// \f(q=[1, \mathbf{0}]\f).
    /// </summary>
    static const Quaternion<T> IDENTITY;

    // For compatibility with std::size().
    constexpr std::size_t size() const noexcept;

    // For compatibility with std::data().
    constexpr T*       data() noexcept;
    constexpr const T* data() const noexcept;

    /// <summary>
    /// Default construct a quaternion.
    /// </summary>
    /// <remarks>
    /// The quaternion is initialized to identity:
    /// \f(q=[1, \mathbf{0}]\f)
    /// </remarks>
    constexpr Quaternion() noexcept;

    /// <summary>
    /// Construct a quaternion from 4 scalar components.
    /// </summary>
    /// <param name="w">The w (scalar) component.</param>
    /// <param name="x">The x (vector) component.</param>
    /// <param name="y">The y (vector) component.</param>
    /// <param name="z">The z (vector) component.</param>
    template<ConvertibleTo<T> W, ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z>
    constexpr Quaternion( W w, X x, Y y, Z z ) noexcept;

    /// <summary>
    /// Construct a quaternion from a 3-component vector and a scalar component.
    /// </summary>
    /// <param name="w">The scalar part.</param>
    /// <param name="v">The vector part.</param>
    template<ConvertibleTo<T> W, ConvertibleTo<T> U>
    constexpr Quaternion( W w, const Vector<U, 3>& v ) noexcept;

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="rhs">The quaternion to copy.</param>
    template<ConvertibleTo<T> U>
    constexpr Quaternion( const Quaternion<U>& rhs ) noexcept;

    /// <summary>
    /// Construct a quaternion from euler angles (in radians).
    /// </summary>
    /// <param name="eulerAngles">The euler angles (pitch, yaw, roll) in radians.</param>
    template<ConvertibleTo<T> U>
    explicit constexpr Quaternion( const Vector<U, 3>& eulerAngles );

    /// <summary>
    /// Construct a quaternion from two (normalized) direction vectors
    /// that represent a rotation from \f(u\f) to \f(v\f).
    /// </summary>
    /// <seealso href="http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final"/>
    /// <param name="u">The first direction vector to rotate from.</param>
    /// <param name="v">The second direction vector to rotate to.</param>
    constexpr Quaternion( const Vector<T, 3>& u, const Vector<T, 3>& v );

    /// <summary>
    /// Construct a quaternion from a 3x3 rotation matrix.
    /// </summary>
    /// <seealso cref="fromMat3"/>
    /// <param name="m">The rotation matrix.</param>
    constexpr explicit Quaternion( const Matrix<T, 3>& m ) noexcept;

    /// <summary>
    /// Construct a quaternion from a 4x4 rotation matrix.
    /// </summary>
    /// <remarks>Only the top-left 3x3 is considered.</remarks>
    /// <seealso cref="fromMat4"/>
    /// <param name="m">The rotation matrix.</param>
    constexpr explicit Quaternion( const Matrix<T, 4>& m ) noexcept;

    /// <summary>
    /// Explicit conversion to a 3x3 rotation matrix.
    /// </summary>
    /// <returns>The 3x3 rotation matrix.</returns>
    constexpr explicit operator Matrix<T, 3>() const noexcept;

    /// <summary>
    /// Explicit conversion to a 4x4 rotation matrix.
    /// </summary>
    /// <returns></returns>
    constexpr explicit operator Matrix<T, 4>() const noexcept;

    /// <summary>
    /// Get the quaternion component at index i.
    /// </summary>
    /// <remarks>
    /// The quaternion is stored with the scalar part in the
    /// the first component and the vector part in the next 3
    /// components:
    /// \f[ q=[s, x, y, z] \f]
    /// There are no check to see if `i` is in the range [0..3].
    /// </remarks>
    /// <param name="i">The index of the component to retrieve.</param>
    /// <returns>A reference to the component at index `i`.</returns>
    constexpr T& operator[]( std::size_t i ) noexcept;

    /// <summary>
    /// Get the quaternion component at index i.
    /// </summary>
    /// <remarks>
    /// The quaternion is stored with the scalar part in the
    /// the first component and the vector part in the next 3
    /// components:
    /// \f[ q=[s, x, y, z] \f]
    /// There are no check to see if `i` is in the range [0..3].
    /// </remarks>
    /// <param name="i">The index of the component to retrieve.</param>
    /// <returns>A reference to the component at index `i`.</returns>
    constexpr const T& operator[]( std::size_t i ) const noexcept;

    /// <summary>
    /// Unary plus operator.
    /// </summary>
    /// <remarks>
    /// This just returns a copy of the quaternion.
    /// </remarks>
    /// <returns>A copy of this quaternion.</returns>
    constexpr Quaternion<T> operator+() const noexcept;

    /// <summary>
    /// Unary minus operator.
    /// </summary>
    /// <returns>A copy of this quaternion with all of the components negated.</returns>
    constexpr Quaternion<T> operator-() const noexcept;

    /// <summary>
    /// Assignment operator.
    /// </summary>
    /// <param name="rhs">The quaternion to assign to this one.</param>
    /// <returns>A reference to this quaternion, after assignment.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion<T>& operator=( const Quaternion<U>& rhs ) noexcept;

    /// <summary>
    /// Addition and assignment operator.
    /// </summary>
    /// <param name="rhs">The quaternion to add to this one.</param>
    /// <returns>A reference to this quaternion, after addition.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion<T>& operator+=( const Quaternion<U>& rhs ) noexcept;

    /// <summary>
    /// Subtraction and assignment operator.
    /// </summary>
    /// <param name="rhs">Th quaternion to subtract from this one.</param>
    /// <returns>A reference to this quaternion, after subtraction.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion<T>& operator-=( const Quaternion<U>& rhs ) noexcept;

    /// <summary>
    /// Quaternion multiplication.
    /// </summary>
    /// <param name="rhs">The quaternion to multiply with this one.</param>
    /// <returns>A reference to this quaternion, after multiplication.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion<T>& operator*=( const Quaternion<U>& rhs ) noexcept;

    /// <summary>
    /// Multiply this quaternion by a scalar.
    /// </summary>
    /// <param name="s">The scalar to multiply this quaternion.</param>
    /// <returns>A reference to this quaternion, after scalar multiplication.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion& operator*=( U s );

    /// <summary>
    /// Divide this quaternion by a scalar.
    /// </summary>
    /// <param name="s">The scalar to divide this quaternion.</param>
    /// <returns>A reference to this quaternion, after scalar division.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion& operator/=( U s );

    /// <summary>
    /// Quaternion addition.
    /// </summary>
    /// <param name="rhs">The quaternion to add to this one.</param>
    /// <returns>The sum of this quaternion and `rhs`.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion operator+( const Quaternion<U>& rhs ) const noexcept;

    /// <summary>
    /// Quaternion subtraction.
    /// </summary>
    /// <param name="rhs">The quaternion to subtract with this one.</param>
    /// <returns>The result of subtracting `rhs` from this quaternion.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion operator-( const Quaternion<U>& rhs ) const noexcept;

    /// <summary>
    /// Quaternion multiplication.
    /// </summary>
    /// <param name="rhs">The quaternion to multiply with this one.</param>
    /// <returns>The result of multiplying this quaternion with `rhs`.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion operator*( const Quaternion<U>& rhs ) const noexcept;

    /// <summary>
    /// Transform a 3-component vector by a quaternion.
    /// </summary>
    /// <param name="v">The vector to rotate.</param>
    /// <returns>The transformed vector.</returns>
    template<ConvertibleTo<T> U>
    constexpr Vector<U, 3> operator*( const Vector<U, 3>& v ) const noexcept;

    /// <summary>
    /// Transform a 4-component vector by a quaternion.
    /// </summary>
    /// <param name="v">The vector to rotate.</param>
    /// <returns>The transformed vector.</returns>
    template<ConvertibleTo<T> U>
    constexpr Vector<U, 4> operator*( const Vector<U, 4>& v ) const noexcept;

    /// <summary>
    /// Multiply by a scalar.
    /// </summary>
    /// <param name="s">The scalar to multiply this quaternion with.</param>
    /// <returns>The result of multiplying this quaternion by a scalar.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion operator*( U s ) const noexcept;

    /// <summary>
    /// Divide by a scalar.
    /// </summary>
    /// <param name="s">The scalar to divide this quaternion with.</param>
    /// <returns>The result of dividing this quaternion by a scalar.</returns>
    template<ConvertibleTo<T> U>
    constexpr Quaternion operator/( U s ) const;

    /// <summary>
    /// Equality comparison.
    /// </summary>
    /// <param name="rhs">The quaternion to compare to this one.</param>
    /// <returns></returns>
    constexpr bool operator==( const Quaternion& rhs ) const noexcept;

    /// <summary>
    /// Inequality comparison.
    /// </summary>
    /// <param name="rhs">The quaternion to compare to this one.</param>
    /// <returns></returns>
    constexpr bool operator!=( const Quaternion& rhs ) const noexcept;
};

/// <summary>
/// Single-precision floating-point quaternion.
/// </summary>
using QuaternionF = Quaternion<float>;

/// <summary>
/// Double-precision floating-point quaternion.
/// </summary>
using QuaternionD = Quaternion<double>;

/// <summary>
/// Alias of a single-precision floating-point quaternion.
/// </summary>
using quat = Quaternion<float>;

/// <summary>
/// Alias of a double-precision floating-point quaternion.
/// </summary>
using dquat = Quaternion<double>;

template<typename T>
inline const Quaternion<T> Quaternion<T>::IDENTITY { T( 1 ), T( 0 ), T( 0 ), T( 0 ) };

template<typename T>
constexpr std::size_t Quaternion<T>::size() const noexcept
{
    return 4u;
}

template<typename T>
constexpr T* Quaternion<T>::data() noexcept
{
    return &base::quat[0];
}

template<typename T>
constexpr const T* Quaternion<T>::data() const noexcept
{
    return &base::quat[0];
}

template<typename T>
constexpr Quaternion<T>::Quaternion() noexcept = default;

template<typename T>
template<ConvertibleTo<T> W, ConvertibleTo<T> X, ConvertibleTo<T> Y, ConvertibleTo<T> Z>
constexpr Quaternion<T>::Quaternion( W w, X x, Y y, Z z ) noexcept
{
    base::w = static_cast<T>( w );
    base::x = static_cast<T>( x );
    base::y = static_cast<T>( y );
    base::z = static_cast<T>( z );
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>::Quaternion( const Vector<U, 3>& eulerAngles )
{
    auto c = cos<T>( eulerAngles * T( 0.5 ) );
    auto s = sin<T>( eulerAngles * T( 0.5 ) );

    base::w = c.x * c.y * c.z + s.x * s.y * s.z;
    base::x = s.x * c.y * c.z - c.x * s.y * s.z;
    base::y = c.x * s.y * c.z + s.x * c.y * s.z;
    base::z = c.x * c.y * s.z - s.x * s.y * c.z;
}

template<typename T>
constexpr Quaternion<T>::Quaternion( const Vector<T, 3>& u, const Vector<T, 3>& v )
{
    // u and v must be normalized.
    assert( isNormalized( u ) );
    assert( isNormalized( v ) );

    const T uv = std::sqrt( dot( u, u ) * dot( v, v ) );
    base::s    = uv + dot( u, v );

    if ( base::s < T( 1e-6 ) * uv )
    {
        base::s   = 0;
        base::vec = std::abs( u.x ) > std::abs( u.z ) ? Vector<T, 3> { -u.y, u.x, T( 0 ) } : Vector<T, 3> { T( 0 ), -u.z, u.y };
    }
    else
    {
        base::vec = cross( u, v );
    }

    // Normalize.
    const T l = T( 1 ) / length( *this );

    base::s *= l;
    base::x *= l;
    base::y *= l;
    base::z *= l;
}

template<typename T>
template<ConvertibleTo<T> W, ConvertibleTo<T> U>
constexpr Quaternion<T>::Quaternion( W w, const Vector<U, 3>& v ) noexcept
{
    base::w   = static_cast<T>( w );
    base::vec = v;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>::Quaternion( const Quaternion<U>& rhs ) noexcept
{
    base::w = static_cast<T>( rhs.w );
    base::x = static_cast<T>( rhs.x );
    base::y = static_cast<T>( rhs.y );
    base::z = static_cast<T>( rhs.z );
}

/// <summary>
/// Create a quaternion from a 3x3 rotation matrix.
/// \f[ q = \left[\frac{\sqrt{1+m_{00}+m_{11}+m_{22}}}{2}, \frac{m_{21}-m_{12}}{4q_w}, \frac{m_{02}-m_{20}}{4q_w}, \frac{m_{10}-m_{01}}{4q_w}\right] \f]
/// </summary>
/// <seealso href="https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/"/>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="m">The 3x3 rotation matrix.</param>
/// <returns>The resulting quaternion.</returns>
template<typename T>
constexpr Quaternion<T> fromMat3( const Matrix<T, 3>& m ) noexcept
{
    const T trace = m[0][0] + m[1][1] + m[2][2];

    if ( trace > T( 0 ) )
    {
        const T s = T( 0.5 ) / std::sqrt( trace + T( 1 ) );
        return {
            T( 0.25 ) / s,
            ( m[2][1] - m[1][2] ) * s,
            ( m[0][2] - m[2][0] ) * s,
            ( m[1][0] - m[0][1] ) * s
        };
    }

    if ( m[0][0] > m[1][1] && m[0][0] > m[2][2] )
    {
        const T s = T( 2 ) * std::sqrt( T( 1 ) + m[0][0] - m[1][1] - m[2][2] );
        return {
            ( m[2][1] - m[1][2] ) / s,
            T( 0.25 ) * s,
            ( m[0][1] + m[1][0] ) / s,
            ( m[0][2] + m[2][0] ) / s
        };
    }

    if ( m[1][1] > m[2][2] )
    {
        const T s = T( 2 ) * std::sqrt( T( 1 ) + m[1][1] - m[0][0] - m[2][2] );
        return {
            ( m[0][2] - m[2][0] ) / s,
            ( m[0][1] + m[1][0] ) / s,
            T( 0.25 ) * s,
            ( m[1][2] + m[2][1] ) / s
        };
    }

    const T s = T( 2 ) * std::sqrt( T( 1 ) + m[2][2] - m[0][0] - m[1][1] );
    return {
        ( m[1][0] - m[0][1] ) / s,
        ( m[0][2] + m[2][0] ) / s,
        ( m[1][2] + m[2][1] ) / s,
        T( 0.25 ) * s
    };
}

/// <summary>
/// Create a quaternion from a 3x3 rotation matrix.
/// \f[ q = \left[\frac{\sqrt{1+m_{00}+m_{11}+m_{22}}}{2}, \frac{m_{21}-m_{12}}{4q_w}, \frac{m_{02}-m_{20}}{4q_w}, \frac{m_{10}-m_{01}}{4q_w}\right] \f]
/// </summary>
/// <remarks>
/// This is just an alias for the ls::fromMat3 function.
/// </remarks>
/// <seealso href="https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/"/>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="m">The 3x3 rotation matrix.</param>
/// <returns>The resulting quaternion.</returns>
template<typename T>
constexpr Quaternion<T> toQuat( const Matrix<T, 3>& m ) noexcept
{
    return fromMat3( m );
}

template<typename T>
constexpr Quaternion<T>::Quaternion( const Matrix<T, 3>& m ) noexcept
: Quaternion( fromMat3( m ) )
{}

/// <summary>
/// Create a quaternion from a 4x4 rotation matrix.
/// \f[ q = \left[\frac{\sqrt{1+m_{00}+m_{11}+m_{22}}}{2}, \frac{m_{21}-m_{12}}{4q_w}, \frac{m_{02}-m_{20}}{4q_w}, \frac{m_{10}-m_{01}}{4q_w}\right] \f]
/// </summary>
/// <seealso href="https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/"/>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="m">The 4x4 rotation matrix.</param>
/// <returns>The resulting quaternion.</returns>
template<typename T>
constexpr Quaternion<T> fromMat4( const Matrix<T, 4>& m ) noexcept
{
    return fromMat3( Matrix<T, 3>( m ) );
}

/// <summary>
/// Create a quaternion from a 4x4 rotation matrix.
/// \f[ q = \left[\frac{\sqrt{1+m_{00}+m_{11}+m_{22}}}{2}, \frac{m_{21}-m_{12}}{4q_w}, \frac{m_{02}-m_{20}}{4q_w}, \frac{m_{10}-m_{01}}{4q_w}\right] \f]
/// </summary>
/// <remarks>
/// This is just an alias for `ls::fromMat4`.
/// </remarks>
/// <seealso href="https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/"/>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="m">The 4x4 rotation matrix.</param>
/// <returns>The resulting quaternion.</returns>
template<typename T>
constexpr Quaternion<T> toQuat( const Matrix<T, 4>& m ) noexcept
{
    return fromMat4( m );
}

template<typename T>
constexpr Quaternion<T>::Quaternion( const Matrix<T, 4>& m ) noexcept
: Quaternion( fromMat4( m ) )
{}

/// <summary>
/// Convert a quaternion to a 3x3 rotation matrix.
/// \f[ \mathbf{R}_q = \begin{bmatrix}
/// 1 - 2y^2 - 2z^2 & 2xy - 2wz & 2xz + wy \\ 2xy + 2wz & 1 - 2x^2 - 2z^2 & 2yz - 2wx \\ 2xz - 2wy & 2yz + 2wx & 1 - 2x^2 - 2y^2
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to convert.</param>
/// <returns>A 3x3 rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 3> toMat3( const Quaternion<T>& q ) noexcept
{
    const T xx( q.x * q.x );
    const T yy( q.y * q.y );
    const T zz( q.z * q.z );
    const T xz( q.x * q.z );
    const T xy( q.x * q.y );
    const T yz( q.y * q.z );
    const T wx( q.w * q.x );
    const T wy( q.w * q.y );
    const T wz( q.w * q.z );

    return {
        T( 1 ) - T( 2 ) * ( yy + zz ),
        T( 2 ) * ( xy - wz ),
        T( 2 ) * ( xz + wy ),
        T( 2 ) * ( xy + wz ),
        T( 1 ) - T( 2 ) * ( xx + zz ),
        T( 2 ) * ( yz - wx ),
        T( 2 ) * ( xz - wy ),
        T( 2 ) * ( yz + wx ),
        T( 1 ) - T( 2 ) * ( xx + yy ),
    };
}

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 3>() const noexcept
{
    return toMat3( *this );
}

/// <summary>
/// Convert a quaternion to a 4x4 rotation matrix.
/// \f[ \mathbf{R}_q = \begin{bmatrix}
/// 1 - 2y^2 - 2z^2 & 2xy - 2wz & 2xz + wy & 0 \\ 2xy + 2wz & 1 - 2x^2 - 2z^2 & 2yz - 2wx & 0 \\ 2xz - 2wy & 2yz + 2wx & 1 - 2x^2 - 2y^2 & 0 \\ 0 & 0 & 0 & 1
/// \end{bmatrix} \f]
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>A 4x4 rotation matrix.</returns>
template<typename T>
constexpr Matrix<T, 4> toMat4( const Quaternion<T>& q ) noexcept
{
    const T xx( q.x * q.x );
    const T yy( q.y * q.y );
    const T zz( q.z * q.z );
    const T xz( q.x * q.z );
    const T xy( q.x * q.y );
    const T yz( q.y * q.z );
    const T wx( q.w * q.x );
    const T wy( q.w * q.y );
    const T wz( q.w * q.z );

    return {
        T( 1 ) - T( 2 ) * ( yy + zz ), T( 2 ) * ( xy - wz ), T( 2 ) * ( xz + wy ), T( 0 ),
        T( 2 ) * ( xy + wz ), T( 1 ) - T( 2 ) * ( xx + zz ), T( 2 ) * ( yz - wx ), T( 0 ),
        T( 2 ) * ( xz - wy ), T( 2 ) * ( yz + wx ), T( 1 ) - T( 2 ) * ( xx + yy ), T( 0 ),
        T( 0 ), T( 0 ), T( 0 ), T( 1 )
    };
}

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 4>() const noexcept
{
    return toMat4( *this );
}

template<typename T>
constexpr T& Quaternion<T>::operator[]( std::size_t i ) noexcept
{
    assert( i < 4 );

    return base::quat[i];
}

template<typename T>
constexpr const T& Quaternion<T>::operator[]( std::size_t i ) const noexcept
{
    assert( i < 4 );

    return base::quat[i];
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator+() const noexcept
{
    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator-() const noexcept
{
    return { base::w, -base::x, -base::y, -base::z };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator=( const Quaternion<U>& rhs ) noexcept
{
    base::w = static_cast<T>( rhs.w );
    base::x = static_cast<T>( rhs.x );
    base::y = static_cast<T>( rhs.y );
    base::z = static_cast<T>( rhs.z );

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator+=( const Quaternion<U>& rhs ) noexcept
{
    base::w += static_cast<T>( rhs.w );
    base::x += static_cast<T>( rhs.x );
    base::y += static_cast<T>( rhs.y );
    base::z += static_cast<T>( rhs.z );

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator-=( const Quaternion<U>& rhs ) noexcept
{
    base::w -= static_cast<T>( rhs.w );
    base::x -= static_cast<T>( rhs.x );
    base::y -= static_cast<T>( rhs.y );
    base::z -= static_cast<T>( rhs.z );

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator*=( const Quaternion<U>& rhs ) noexcept
{
    const Quaternion<T> q1 { *this };
    const Quaternion<T> q2 { rhs };

    base::w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    base::x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    base::y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    base::z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator*=( U s )
{
    base::w *= static_cast<T>( s );
    base::x *= static_cast<T>( s );
    base::y *= static_cast<T>( s );
    base::z *= static_cast<T>( s );

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T>& Quaternion<T>::operator/=( U s )
{
    assert( s != U( 0 ) );

    const T invS = T( 1 ) / static_cast<T>( s );

    base::w *= invS;
    base::x *= invS;
    base::y *= invS;
    base::z *= invS;

    return *this;
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T> Quaternion<T>::operator+( const Quaternion<U>& rhs ) const noexcept
{
    return {
        base::w + static_cast<T>( rhs.w ),
        base::x + static_cast<T>( rhs.x ),
        base::y + static_cast<T>( rhs.y ),
        base::z + static_cast<T>( rhs.z ),
    };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T> Quaternion<T>::operator-( const Quaternion<U>& rhs ) const noexcept
{
    return {
        base::w - static_cast<T>( rhs.w ),
        base::x - static_cast<T>( rhs.x ),
        base::y - static_cast<T>( rhs.y ),
        base::z - static_cast<T>( rhs.z ),
    };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T> Quaternion<T>::operator*( const Quaternion<U>& rhs ) const noexcept
{
    const Quaternion<T> q2 { rhs };

    return {
        base::w * q2.w - base::x * q2.x - base::y * q2.y - base::z * q2.z,
        base::w * q2.x + base::x * q2.w + base::y * q2.z - base::z * q2.y,
        base::w * q2.y - base::x * q2.z + base::y * q2.w + base::z * q2.x,
        base::w * q2.z + base::x * q2.y - base::y * q2.x + base::z * q2.w,
    };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Vector<U, 3> Quaternion<T>::operator*( const Vector<U, 3>& v ) const noexcept
{
    const Vector<T, 3> qv { base::x, base::y, base::z };
    const Vector<T, 3> uv  = cross( qv, v );
    const Vector<T, 3> uuv = cross( qv, uv );

    return v + ( uv * base::w + uuv ) * T( 2 );
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Vector<U, 4> Quaternion<T>::operator*( const Vector<U, 4>& v ) const noexcept
{
    return { *this * Vector<U, 3> { v }, v.w };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T> Quaternion<T>::operator*( U s ) const noexcept
{
    return {
        base::w * static_cast<T>( s ),
        base::x * static_cast<T>( s ),
        base::y * static_cast<T>( s ),
        base::z * static_cast<T>( s ),
    };
}

template<typename T>
template<ConvertibleTo<T> U>
constexpr Quaternion<T> Quaternion<T>::operator/( U s ) const
{
    assert( s != U( 0 ) );

    const T invS = T( 1 ) / static_cast<T>( s );

    return *this * invS;
}

template<typename T>
constexpr bool Quaternion<T>::operator==( const Quaternion& rhs ) const noexcept
{
    return base::w == rhs.w && base::x == rhs.x && base::y == rhs.y && base::z == rhs.z;
}

template<typename T>
constexpr bool Quaternion<T>::operator!=( const Quaternion& rhs ) const noexcept
{
    return !( *this == rhs );
}

/// <summary>
/// Compute the dot product between two quaternions.
/// </summary>
/// <remarks>
/// This is equivalent to vector dot product.
/// </remarks>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q1">The first quaternion.</param>
/// <param name="q2">The second quaternion.</param>
/// <returns>The dot product of q1 and q2.</returns>
template<typename T>
constexpr T dot( const Quaternion<T>& q1, const Quaternion<T>& q2 )
{
    return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

/// <summary>
/// Compute the squared length of the quaternion.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>The squared length of the quaternion.</returns>
template<typename T>
constexpr T lengthSqr( const Quaternion<T>& q ) noexcept
{
    return dot( q, q );
}

/// <summary>
/// Compute the length of the quaternion.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>The length of the quaternion.</returns>
template<typename T>
constexpr T length( const Quaternion<T>& q ) noexcept
{
    return std::sqrt( lengthSqr( q ) );
}

/// <summary>
/// Normalize the quaternion.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to normalize.</param>
/// <returns>The normalized quaternion.</returns>
template<typename T>
constexpr Quaternion<T> normalize( const Quaternion<T>& q ) noexcept
{
    const T l = length( q );

    if ( l > T( 0 ) )
    {
        return q / l;
    }

    return Quaternion<T>::IDENTITY;
}

/// <summary>
/// Check to see if a quaternion is normalized.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to check.</param>
/// <param name="epsilon">(Optional) error tolerance.</param>
/// <returns>`true` if the quaternion is normalized, `false` otherwise.</returns>
template<typename T>
constexpr bool isNormalized( const Quaternion<T>& q, T epsilon = EPSILON<T> ) noexcept
{
    return ( std::abs( T( 1 ) - lengthSqr( q ) ) < epsilon );
}

/// <summary>
/// Quaternion cross product.
/// </summary>
/// <remarks>
/// This is equivalent to quaternion multiplication.
/// </remarks>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q1">The first quaternion.</param>
/// <param name="q2">The second quaternion.</param>
/// <returns></returns>
template<typename T>
constexpr Quaternion<T> cross( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
{
    return {
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
    };
}

/// <summary>
/// Quaternion conjugate.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to compute the conjugate of.</param>
/// <returns>The quaternion conjugate.</returns>
template<typename T>
constexpr Quaternion<T> conjugate( const Quaternion<T>& q ) noexcept
{
    return { q.w, -q.x, -q.y, -q.z };
}

/// <summary>
/// Quaternion inverse.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to inverse.</param>
/// <returns>The inverse of `q`.</returns>
template<typename T>
constexpr Quaternion<T> inverse( const Quaternion<T>& q ) noexcept
{
    return conjugate( q ) / dot( q, q );
}

/// <summary>
/// Return the angle of rotation (in radians).
/// </summary>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <param name="q">The quaternion to get the angle of.</param>
/// <returns>The angle of rotation (in radians).</returns>
template<typename T>
constexpr T angle( const Quaternion<T>& q ) noexcept
{
    if ( std::abs( q.w ) > COS_ONE_OVER_TWO<T> )
    {
        const T a = std::asin( std::sqrt( q.x * q.x + q.y * q.y + q.z * q.z ) ) * T( 2 );
        if ( q.w < T( 0 ) )
            return TWO_PI<T> - a;
        return a;
    }

    return std::acos( q.w ) * T( 2 );
}

/// <summary>
/// Return the rotation axis of the quaternion.
/// </summary>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <param name="q">The quaternion to get the rotation axis.</param>
/// <param name="v">(optional) The default axis to return if `q` is identity. By default, {0, 0, 1} is used.</param>
/// <returns>The rotation axis of the quaternion.</returns>
template<typename T>
constexpr Vector<T, 3> axis( const Quaternion<T>& q, const Vector<T, 3>& v = { 0, 0, 1 } ) noexcept
{
    T tmp = T( 1 ) - q.w * q.w;

    if ( tmp <= T( 0 ) )
        return v;

    tmp = T( 1 ) / std::sqrt( tmp );

    return { q.x * tmp, q.y * tmp, q.z * tmp };
}

/// <summary>
/// Construct a quaternion from an axis of rotation and an angle (in radians).
/// </summary>
/// <remarks>
/// The axis of rotation must be normalized.
/// </remarks>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <param name="axis">The axis of rotation.</param>
/// <param name="angle">The rotation angle (in radians)</param>
/// <returns></returns>
template<typename T>
constexpr Quaternion<T> axisAngle( const Vector<T, 3>& axis, T angle ) noexcept
{
    assert( isNormalized( axis ) );  // Axis must be normalized.

    const T s = std::sin( angle * T( 0.5 ) );
    const T c = std::cos( angle * T( 0.5 ) );

    return { c, axis * s };
}

/// <summary>
/// Compute the pitch (in radians) of the quaternion rotation.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>The pitch (in radians) of the quaternion.</returns>
template<typename T>
constexpr T pitch( const Quaternion<T>& q ) noexcept
{
    const T x = q.w * q.w - q.x * q.x - q.y * q.y + q.x * q.z;
    const T y = T( 2 ) * ( q.y * q.z + q.w * q.x );

    if ( all( equal( Vector<T, 2> { x, y }, Vector<T, 2> { 0 }, EPSILON<T> ) ) )
        return T( T( 2 ) * std::atan2( q.x, q.w ) );

    return T( std::atan2( y, x ) );
}

/// <summary>
/// Compute the yaw (in radians) of the quaternion rotation.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>The yaw (in radians) of the quaternion.</returns>
template<typename T>
constexpr T yaw( const Quaternion<T>& q ) noexcept
{
    return std::asin( std::clamp( T( -2 ) * ( q.x * q.z - q.w * q.y ), T( -1 ), T( 1 ) ) );
}

/// <summary>
/// Compute the roll (in radians) of the quaternion rotation.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion.</param>
/// <returns>The roll (in radians) of the quaternion.</returns>
template<typename T>
constexpr T roll( const Quaternion<T>& q ) noexcept
{
    const T x = q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z;
    const T y = T( 2 ) * ( q.x * q.y + q.w * q.z );

    if ( all( equal( Vector<T, 2> { x, y }, Vector<T, 2> { 0 }, EPSILON<T> ) ) )
        return T( 0 );

    return T( std::atan2( y, x ) );
}

/// <summary>
/// Get the Euler angles (pitch, yaw, roll in radians) of the quaternion.
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q">The quaternion to extract the angles.</param>
/// <returns>A 3-component vector that contains the pitch, yaw, and roll (in radians).</returns>
template<typename T>
constexpr Vector<T, 3> eulerAngles( const Quaternion<T>& q ) noexcept
{
    return { pitch( q ), yaw( q ), roll( q ) };
}

/// <summary>
/// Quaternion exponential.
/// </summary>
/// <typeparam name="T">The Quaternion type.</typeparam>
/// <param name="q">The Quaternion.</param>
/// <returns>The Quaternion exponential.</returns>
template<typename T>
constexpr Quaternion<T> exp( const Quaternion<T>& q ) noexcept
{
    Vector<T, 3> v { q.x, q.y, q.z };
    const T      a = length( v );

    if ( a < EPSILON<T> )  // Avoid divide by 0 errors.
        return Quaternion<T>::IDENTITY;

    v /= a;  // Normalize.
    return { std::cos( a ), std::sin( a ) * v };
}

/// <summary>
/// Quaternion log.
/// </summary>
/// <typeparam name="T">The Quaternion type.</typeparam>
/// <param name="q">The Quaternion.</param>
/// <returns>The Quaternion log.</returns>
template<typename T>
constexpr Quaternion<T> log( const Quaternion<T>& q ) noexcept
{
    Vector<T, 3> v { q.x, q.y, q.z };
    const T      l = length( v );

    if ( l < EPSILON<T> )
    {
        if ( q.w > T( 0 ) )
            return { std::log( q.w ), T( 0 ), T( 0 ), T( 0 ) };
        if ( q.w < T( 0 ) )
            return { std::log( -q.w ), PI<T>, T( 0 ), T( 0 ) };

        return { INF<T>, INF<T>, INF<T>, INF<T> };
    }

    const T t  = std::atan2( l, q.w ) / l;
    const T l2 = l * l + q.w * q.w;

    return { T( 0.5 ) * std::log( l2 ), t * q.x, t * q.y, t * q.z };
}

/// <summary>
/// Raise a Quaternion to a power.
/// </summary>
/// <typeparam name="T">The Quaternion type.</typeparam>
/// <param name="q">The Quaternion to raise to the power of `exp`.</param>
/// <param name="exp">The exponent power.</param>
/// <returns>\f(q^{exp}\f).</returns>
template<typename T>
constexpr Quaternion<T> pow( const Quaternion<T>& q, T exp ) noexcept
{
    // q^0 results in quaternion identity (1).
    if ( std::abs( exp ) < EPSILON<T> )
        return Quaternion<T>::IDENTITY;

    const T l = length( q );  // Used to normalize in case of non-unit quaternions.

    if ( l < EPSILON<T> )
        return Quaternion<T>::IDENTITY;

    T a;
    if ( std::abs( q.w / l ) > COS_ONE_OVER_TWO<T> )
    {
        // Check for divide by 0 (or very close to 0).
        const T lengthSqr = q.x * q.x + q.y * q.y + q.z * q.z;

        if ( lengthSqr < EPSILON<T> )
            return { std::pow( q.w, exp ), T( 0 ), T( 0 ), T( 0 ) };

        a = std::asin( std::sqrt( lengthSqr ) / l );
    }
    else
    {
        a = std::acos( q.w / l );
    }

    const T a2    = a * exp;
    const T div   = std::sin( a2 ) / std::sin( a );
    const T l2    = std::pow( l, exp - T( 1 ) );
    const T divl2 = div * l2;

    return { std::cos( a2 ) * l * l2, q.x * divl2, q.y * divl2, q.z * divl2 };
}

template<typename T>
constexpr Quaternion<T> sqrt( const Quaternion<T>& q )
{
    return pow( q, T( 0.5 ) );
}

/// <summary>
/// Linear interpolation of two quaternions.
/// </summary>
/// <remarks>
/// This method does not attempt to maintain the length nor
/// does the resulting rotation occur at a constant rate.
/// The resulting quaternion should be renormalized.
/// </remarks>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q0">The starting quaternion.</param>
/// <param name="q1">The ending quaternion.</param>
/// <param name="t">The interpolation factor (in the range [0..1]).</param>
/// <returns>The quaternion that is a linear interpolation between `q0` and `q1`.</returns>
template<typename T>
constexpr Quaternion<T> lerp( const Quaternion<T>& q0, const Quaternion<T>& q1, const T t ) noexcept
{
    assert( t >= T( 0 ) );
    assert( t <= T( 1 ) );

    return q0 * ( T( 1 ) - t ) + q1 * t;
}

/// <summary>
/// Compute an intermediate control point (\f(s_i\f)) for use in squad interpolation.
/// \f[ s_i=\exp\left(-\frac{\log\left(q_{i+1}q_i^{-1}\right)+\log\left(q_{i-1}q_i^{-1}\right)}{4}\right)q_i \f]
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q0">The previous quaternion in the sequence.</param>
/// <param name="q1">The current quaternion to compute the control point for.</param>
/// <param name="q2">The next quaternion in the sequence.</param>
/// <returns>The intermediate control point for \f(q_1\f).</returns>
template<typename T>
constexpr Quaternion<T> intermediate( const Quaternion<T>& q0, const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
{
    const Quaternion<T> q1Inv = inverse( q1 );
    return exp( -( ( log( q2 * q1Inv ) + log( q0 * q1Inv ) ) / T( 4 ) ) ) * q1;
}

/// <summary>
/// Spherical linear interpolation (slerp).
/// \f[ q_t=\frac{\sin(1-t)\theta}{\sin\theta}q_0+\frac{\sin{t\theta}}{\sin\theta}q_1 \f]
/// </summary>
/// <remarks>
/// Unlike linear interpolation, this method maintains magnitude and has constant
/// speed over the rotation arc between q0 and q1.
/// </remarks>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q0">The starting quaternion.</param>
/// <param name="q1">The ending quaternion.</param>
/// <param name="t">The interpolation parameter ([0..1]).</param>
/// <returns>The interpolated quaternion \f(q_t\f).</returns>
template<typename T>
constexpr Quaternion<T> slerp( const Quaternion<T>& q0, const Quaternion<T>& q1, const T t ) noexcept
{
    T c = dot( q0, q1 );  // cosine angle between q0 and q1.

    // If cosine angle is close to 1, then the angle between q0 and q1
    // is very near 0. In this case, just perform a linear interpolation
    // to avoid divide by 0 error (when sin(a) ~= 0).
    if ( c > T( 1 ) - EPSILON<T> )
    {
        return lerp( q0, q1, t );
    }

    Quaternion<T> q = q1;
    // If the cosine angle between q0 and q1 is < 0, then negate q1 so
    // that the interpolation takes the shortest path from q1 to q1.
    if ( c < T( 0 ) )
    {
        q = -q;
        c = -c;
    }

    const T a = std::acos( c );  // Compute the angle.
    return ( q0 * std::sin( ( T( 1 ) - t ) * a ) + q * std::sin( t * a ) ) / std::sin( a );
}

/// <summary>
///  Spherical quadrangle interpolation.
///  \f[ \mathrm{squad}(q_i,q_{i+1},s_i,s_{i+1},t)=\mathrm{slerp}(\mathrm{slerp}(q_i,q_{i+1},t),\mathrm{slerp}(s_i,s_{i+1},t),2t(1-t)) \f]
/// </summary>
/// <typeparam name="T">The quaternion type.</typeparam>
/// <param name="q0">The first quaternion.</param>
/// <param name="q1">The second quaternion.</param>
/// <param name="s0">The first intermediate control point.</param>
/// <param name="s1">The second intermediate control point.</param>
/// <param name="t">The interpolation parameter ([0..1])</param>
/// <returns>The resulting spherical quadrangle interpolation over t.</returns>
template<typename T>
constexpr Quaternion<T> squad( const Quaternion<T>& q0, const Quaternion<T>& q1, const Quaternion<T>& s0, const Quaternion<T>& s1, const T t ) noexcept
{
    return slerp( slerp( q0, q1, t ), slerp( s0, s1, t ), T( 2 ) * t * ( T( 1 ) - t ) );
}

template<typename T>
constexpr Vector<bool, 4> lessThan( const Quaternion<T>& a, const Quaternion<T>& b ) noexcept
{
    Vector<bool, 4> res;

    for ( int i = 0; i < 4; ++i )
        res[i] = a[i] < b[i];

    return res;
}

template<typename T>
constexpr Vector<bool, 4> lessThanEqual( const Quaternion<T>& a, const Quaternion<T>& b ) noexcept
{
    Vector<bool, 4> res;

    for ( int i = 0; i < 4; ++i )
        res[i] = a[i] <= b[i];

    return res;
}

template<typename T>
constexpr Vector<bool, 4> greaterThan( const Quaternion<T>& a, const Quaternion<T>& b ) noexcept
{
    Vector<bool, 4> res;

    for ( int i = 0; i < 4; ++i )
        res[i] = a[i] > b[i];

    return res;
}

template<typename T>
constexpr Vector<bool, 4> greaterThanEqual( const Quaternion<T>& a, const Quaternion<T>& b ) noexcept
{
    Vector<bool, 4> res;

    for ( int i = 0; i < 4; ++i )
        res[i] = a[i] >= b[i];

    return res;
}

template<typename T>
constexpr Vector<bool, 4> equal( const Quaternion<T>& a, const Quaternion<T>& b, const Vector<T, 4>& epsilon = Vector<T, 4>::ZERO ) noexcept
{
    Vector<bool, 4> res;

    for ( int i = 0; i < 4; ++i )
        res[i] = std::abs( a[i] - b[i] ) < epsilon[i];

    return res;
}

template<typename T>
constexpr Vector<bool, 4> equal( const Quaternion<T>& a, const Quaternion<T>& b, T epsilon )
{
    return equal( a, b, Vector<T, 4>( epsilon ) );
}

template<typename T>
constexpr Vector<bool, 4> notEqual( const Quaternion<T>& a, const Quaternion<T>& b, const Vector<T, 4>& epsilon = Vector<T, 4>::ZERO ) noexcept
{
    return negate( equal( a, b, epsilon ) );
}

template<typename T>
constexpr Vector<bool, 4> notEqual( const Quaternion<T>& a, const Quaternion<T>& b, T epsilon )
{
    return notEqual( a, b, Vector<T, 4>( epsilon ) );
}

/// <summary>
/// Pre-multiply a 3-component vector by a quaternion.
/// </summary>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <typeparam name="U">The vector value type.</typeparam>
/// <param name="v">The vector to transform.</param>
/// <param name="q">The quaternion.</param>
/// <returns>The result of transforming the vector by the inverse of the quaternion.</returns>
template<typename T, ConvertibleTo<T> U>
constexpr Vector<U, 3> operator*( const Vector<U, 3>& v, const Quaternion<T>& q )
{
    return inverse( q ) * v;
}

/// <summary>
/// Pre-multiply a 4-component vector by a quaternion.
/// </summary>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <typeparam name="T">The vector value type.</typeparam>
/// <param name="v">The vector to transform.</param>
/// <param name="q">The quaternion.</param>
/// <returns>The result of transforming the vector by the inverse of the quaternion.</returns>
template<typename T, ConvertibleTo<T> U>
constexpr Vector<U, 4> operator*( const Vector<U, 4>& v, const Quaternion<T>& q )
{
    return inverse( q ) * v;
}

/// <summary>
/// Pre multiply a scalar by a quaternion.
/// </summary>
/// <typeparam name="T">The quaternion value type.</typeparam>
/// <typeparam name="U">The scalar value type.</typeparam>
/// <param name="s">The scalar value.</param>
/// <param name="q">The quaternion.</param>
/// <returns>The scaled quaternion.</returns>
template<typename T, ConvertibleTo<T> U>
constexpr Quaternion<T> operator*( U s, const Quaternion<T>& q )
{
    return q * s;
}

}  // namespace FastMath
