#pragma once

#include "Concepts.hpp"

#include <cstdint>
#include <limits>

namespace FastMath
{

/// <summary>
/// Constant for \f(\pi\f).
/// </summary>
template<FloatingPoint T>
constexpr T PI = T( 3.1415926535897932384626433832795 );

/// <summary>
/// Constant for \f(\frac{\pi}{2}\f).
/// </summary>
template<FloatingPoint T>
constexpr T PI_OVER_TWO = PI<T> / T( 2 );

/// <summary>
/// Constant for \f(2\pi\f).
/// </summary>
template<FloatingPoint T>
constexpr T TWO_PI = PI<T> * T( 2 );

/// <summary>
/// Constant for \f(\cos(\frac{1}{2})\f).
/// </summary>
template<FloatingPoint T>
constexpr T COS_ONE_OVER_TWO = T( 0.87758256189037271611628158260383 );

/// <summary>
/// Constant for \f(\epsilon\f).
/// </summary>
/// <remarks>
/// This value represents the smallest representable floating-point value that is not 0.
/// </remarks>
template<FloatingPoint T>
constexpr T EPSILON = std::numeric_limits<T>::epsilon();

/// <summary>
/// Constant for \f(\infty\f).
/// </summary>
template<HasInfinity T>
constexpr T INF = std::numeric_limits<T>::infinity();

/// <summary>
/// Convert from radians to degrees.
/// </summary>
/// <param name="radians">The value in radians.</param>
/// <returns>The value in degrees.</returns>
template<FloatingPoint T>
constexpr T degrees( const T radians ) noexcept
{
    return radians * ( T( 180.0 ) / PI<T> );
}

/// <summary>
/// Convert from degrees to radians.
/// </summary>
/// <param name="degrees">The value in degrees.</param>
/// <returns>The value in radians.</returns>
template<FloatingPoint T>
constexpr T radians( const T degrees ) noexcept
{
    return degrees * ( PI<T> / T( 180.0 ) );
}

/// <summary>
/// Compute the normalized value in the range [min..max].
/// </summary>
/// <param name="x">The value to normalize.</param>
/// <param name="min">The minimum value.</param>
/// <param name="max">The maximum value.</param>
/// <returns>`0` if `x` is `min`, `1` if `x` is `max`, `0.5` if `x` is half-way between `min` and `max`, otherwise the normalized value in the range [0..1].</returns>
template<Arithmetic T, Arithmetic U>
constexpr T normalizeRange( U x, U min, U max ) noexcept
{
    return T( x - min ) / T( max - min );
}

/// <summary>
/// Compute a value that is scaled and translated by `bias` and `shift` respectfully.
/// </summary>
/// <remarks>
/// This method first scales then shifts `x`:
/// <code>
/// return x * bias + shift;
/// </code>
/// </remarks>
/// <param name="x">The value to shift and bias.</param>
/// <param name="shift">The value to translate `x`.</param>
/// <param name="bias">The value to scale `x`.</param>
/// <returns></returns>
template<Arithmetic T, Arithmetic U>
constexpr T shiftBias( U x, U shift, U bias ) noexcept
{
    return T( x * bias ) + T( shift );
}

/// <summary>
/// Align a value up according to the mask.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <param name="value">The value to align.</param>
/// <param name="mask">The mask to use for the alignment.</param>
/// <returns>The aligned value.</returns>
template<Integral T>
constexpr T alignUpWithMask( T value, std::size_t mask ) noexcept
{
    return T( ( static_cast<std::size_t>( value ) + mask ) & ~mask );
}

/// <summary>
/// Align a value down according to a mask.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <param name="value">The value to align.</param>
/// <param name="mask">The mask to use for the alignment.</param>
/// <returns>The aligned value.</returns>
template<Integral T>
constexpr T alignDownWithMask( T value, std::size_t mask ) noexcept
{
    return T( static_cast<std::size_t>( value ) & ~mask );
}

/// <summary>
/// Align a value up according to a specific alignment.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <param name="value">The value to align.</param>
/// <param name="alignment">The required alignment.</param>
/// <returns>The aligned value.</returns>
template<Integral T>
constexpr T alignUp( T value, std::size_t alignment ) noexcept
{
    return alignUpWithMask( value, alignment - 1 );
}

/// <summary>
/// Align a value down according to a specific alignment.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <param name="value">The value to align.</param>
/// <param name="alignment">The required alignment.</param>
/// <returns>The aligned value.</returns>
template<Integral T>
constexpr T alignDown( T value, std::size_t alignment ) noexcept
{
    return alignDownWithMask( value, alignment - 1 );
}

/// <summary>
/// Check to see if a value is aligned.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <param name="value">The value to check.</param>
/// <param name="alignment">The required alignment.</param>
/// <returns>`true` if `value` is aligned to `alignment`, `false` otherwise.</returns>
template<Integral T>
constexpr bool isAligned( T value, std::size_t alignment ) noexcept
{
    return 0 == ( static_cast<std::size_t>( value ) & ( alignment - 1 ) );
}

/// <summary>
/// Divide a value by a multiple of the alignment.
/// </summary>
/// <seealso href="https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h"/>
/// <typeparam name="T">The value type.</typeparam>
/// <param name="value">The value to divide.</param>
/// <param name="alignment">The alignment to divide.</param>
/// <returns>The result of dividing by a multiple of `alignment`.</returns>
template<typename T>
constexpr T divideByMultiple( T value, std::size_t alignment ) noexcept
{
    return static_cast<T>( ( value + alignment - 1 ) / alignment );
}

/// <summary>
/// Get the next highest power of two.
/// </summary>
/// <seealso href="http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2"/>
/// <param name="v">The value to round up to the next highest power of two.</param>
/// <returns>The next highest power of two.</returns>
constexpr uint32_t nextHighestPow2( uint32_t v ) noexcept
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v;
}

/// <summary>
/// Get the next highest power of two.
/// </summary>
/// <seealso href="http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2"/>
/// <param name="v">The value to round up to the next highest power of two.</param>
/// <returns>The next highest power of two.</returns>
constexpr uint64_t nextHighestPow2( uint64_t v ) noexcept
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;

    return v;
}

}  // namespace FastMath
