#pragma once

#include <cmath>
#include <cstdint>

namespace FastMath
{
template<typename T>
inline constexpr T PI = T( 3.1415926535897932384626433832795 );

template<typename T>
inline constexpr T _2PI = T( 2 ) * PI<T>;

// Convert radians to degrees.
template<typename T>
inline constexpr T degrees( T radians ) noexcept
{
    return radians * ( T( 180 ) / PI<T> );
}

// Convert degrees to radians.
template<typename T>
inline constexpr T radians( T degrees ) noexcept
{
    return degrees * ( PI<T> / T( 180 ) );
}

template<typename T>
inline constexpr T deadzone( T val, T deadzone ) noexcept
{
    if ( std::abs( val ) < deadzone )
    {
        return T( 0 );
    }

    return val;
}

// Normalize a value in the range [min - max]
template<typename T, typename U>
inline constexpr T normalizeRange( U x, U min, U max ) noexcept
{
    return T( x - min ) / T( max - min );
}

// Shift and bias a value into another range.
template<typename T, typename U>
inline constexpr T shiftBias( U x, U shift, U bias ) noexcept
{
    return T( x * bias ) + T( shift );
}

/***************************************************************************
 * These functions were taken from the MiniEngine.
 * Source code available here:
 * https://github.com/Microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Math/Common.h
 * Retrieved: January 13, 2016
 **************************************************************************/
template<typename T>
inline constexpr T alignUpWithMask( T value, size_t mask ) noexcept
{
    return (T)( ( (size_t)value + mask ) & ~mask );
}

template<typename T>
inline constexpr T alignDownWithMask( T value, size_t mask ) noexcept
{
    return (T)( (size_t)value & ~mask );
}

template<typename T>
inline constexpr T alignUp( T value, size_t alignment ) noexcept
{
    return alignUpWithMask( value, alignment - 1 );
}

template<typename T>
inline constexpr T alignDown( T value, size_t alignment ) noexcept
{
    return alignDownWithMask( value, alignment - 1 );
}

template<typename T>
inline constexpr bool isAligned( T value, size_t alignment ) noexcept
{
    return 0 == ( (size_t)value & ( alignment - 1 ) );
}

template<typename T>
inline constexpr T divideByMultiple( T value, size_t alignment ) noexcept
{
    return (T)( ( value + alignment - 1 ) / alignment );
}
/***************************************************************************/

/**
 * Round up to the next highest power of 2.
 * @source: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
 * @retrieved: January 16, 2016
 */
inline constexpr uint32_t nextHighestPow2( uint32_t v ) noexcept
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

/**
 * Round up to the next highest power of 2.
 * @source: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
 * @retrieved: January 16, 2016
 */
inline constexpr uint64_t nextHighestPow2( uint64_t v ) noexcept
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
