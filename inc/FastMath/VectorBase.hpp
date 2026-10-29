#pragma once

#include "Config.hpp"

#include <cassert>
#include <cstddef>

namespace FastMath
{
// Vectors with 2, 3, or 4 components store their components as plain `x`, `y`, `z`, `w` members,
// so every member can be read in constant expressions (unlike a union of an array and an anonymous struct).
//
// `operator[]` indexes the members directly at runtime: `( &x )[i]`. The members are tightly packed
// (this is checked by a static_assert in Vector::data()) and MSVC, GCC, and Clang all compile this
// to a single load. Pointer arithmetic across members is not allowed in constant expressions, so at
// compile time the member is selected with a switch instead. (A switch at runtime is not an option:
// MSVC does not optimize it away, which made matrix multiplication about 10x slower.)
//
// `__builtin_is_constant_evaluated()` is what `std::is_constant_evaluated()` calls in the MSVC, GCC, and
// Clang standard libraries. It is used directly because this operator is inlined everywhere, and the
// extra function made optimized builds of code that uses FastMath about 5% slower to compile.

/// <summary>
/// Base class for vectors with any number of components.
/// </summary>
/// <typeparam name="T">The component type.</typeparam>
/// <typeparam name="N">The number of components.</typeparam>
template<typename T, std::size_t N>
struct VectorBase
{
    T elements[N] {};

    constexpr T& operator[]( std::size_t i ) noexcept
    {
        assert( i < N );
        return elements[i];
    }

    constexpr const T& operator[]( std::size_t i ) const noexcept
    {
        assert( i < N );
        return elements[i];
    }
};

/// <summary>
/// Partial specialization for 2-component vectors.
/// </summary>
/// <typeparam name="T">The component type.</typeparam>
template<typename T>
struct VectorBase<T, 2>
{
    T x {}, y {};

    constexpr T& operator[]( std::size_t i ) noexcept
    {
        assert( i < 2 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            }
        }

        return ( &x )[i];
    }

    constexpr const T& operator[]( std::size_t i ) const noexcept
    {
        assert( i < 2 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            }
        }

        return ( &x )[i];
    }
};

/// <summary>
/// Partial specialization for 3-component vectors.
/// </summary>
/// <typeparam name="T">The component type.</typeparam>
template<typename T>
struct VectorBase<T, 3>
{
    T x {}, y {}, z {};

    constexpr T& operator[]( std::size_t i ) noexcept
    {
        assert( i < 3 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }

        return ( &x )[i];
    }

    constexpr const T& operator[]( std::size_t i ) const noexcept
    {
        assert( i < 3 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }

        return ( &x )[i];
    }
};

/// <summary>
/// Partial specialization for 4-component vectors.
/// </summary>
/// <typeparam name="T">The component type.</typeparam>
template<typename T>
struct VectorBase<T, 4>
{
    T x {}, y {}, z {}, w {};

    constexpr T& operator[]( std::size_t i ) noexcept
    {
        assert( i < 4 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        return ( &x )[i];
    }

    constexpr const T& operator[]( std::size_t i ) const noexcept
    {
        assert( i < 4 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        return ( &x )[i];
    }
};

#if defined( FM_SSE )
/// <summary>
/// Specialization for floating-point 4-component vectors.
/// </summary>
/// <remarks>
/// The vector is 16-byte aligned so that it can be loaded into an SSE register with `_mm_load_ps( &v.x )`.
/// </remarks>
template<>
struct alignas( 16 ) VectorBase<float, 4>
{
    float x {}, y {}, z {}, w {};

    constexpr float& operator[]( std::size_t i ) noexcept
    {
        assert( i < 4 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        return ( &x )[i];
    }

    constexpr const float& operator[]( std::size_t i ) const noexcept
    {
        assert( i < 4 );
        if ( __builtin_is_constant_evaluated() )
        {
            switch ( i )
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        return ( &x )[i];
    }
};
#endif

}  // namespace FastMath
