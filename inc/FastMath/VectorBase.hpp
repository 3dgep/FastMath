#pragma once

#include "Config.hpp"

#include <cstddef>

#if LS_COMPILER == LS_COMPILER_CLANG
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
    #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif LS_COMPILER == LS_COMPILER_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#elif LS_COMPILER == LS_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable : 4201 )
#endif

namespace FastMath
{
/// <summary>
/// Base class for vectors.
/// </summary>
/// <typeparam name="T">The component type.</typeparam>
template<typename T, std::size_t N>
struct VectorBase
{
    constexpr VectorBase() noexcept;

    T vec[N];
};

template<typename T, std::size_t N>
constexpr VectorBase<T, N>::VectorBase() noexcept
: vec {}
{}

/// <summary>
/// Partial specialization for 2-component vectors.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct VectorBase<T, 2>
{
    constexpr VectorBase() noexcept;

    union
    {
        struct
        {
            T x, y;
        };
        struct
        {
            T r, g;
        };
        struct
        {
            T s, t;
        };
        struct
        {
            T u, v;
        };
        T vec[2];
    };
};

template<typename T>
constexpr VectorBase<T, 2>::VectorBase() noexcept
: vec {}
{}

/// <summary>
/// Partial specialization for 3-component vectors.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct VectorBase<T, 3>
{
    constexpr VectorBase() noexcept;

    union
    {
        struct
        {
            T x, y, z;
        };
        struct
        {
            T r, g, b;
        };
        T vec[3];
    };
};

template<typename T>
constexpr VectorBase<T, 3>::VectorBase() noexcept
: vec {}
{}

/// <summary>
/// Partial specialization for 4-component vectors.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct VectorBase<T, 4>
{
    constexpr VectorBase() noexcept;

    union
    {
        struct
        {
            T x, y, z, w;
        };
        struct
        {
            T r, g, b, a;
        };
        T vec[4];
    };
};

template<typename T>
constexpr VectorBase<T, 4>::VectorBase() noexcept
: vec {}
{}

#if defined( LS_SSE )
/// <summary>
/// Specialization for floating-point 4-component vectors.
/// </summary>
template<>
struct alignas( 16 ) VectorBase<float, 4>
{
    constexpr VectorBase() noexcept;
    constexpr VectorBase( __m128 v ) noexcept;

    union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            float r, g, b, a;
        };
        float  vec[4];
        __m128 v;
    };

    constexpr operator __m128() const noexcept;
};

constexpr VectorBase<float, 4>::VectorBase() noexcept
: vec {}
{}

constexpr VectorBase<float, 4>::VectorBase( __m128 v ) noexcept
: v { v }
{}

constexpr VectorBase<float, 4>::operator __m128() const noexcept
{
    return v;
}

#endif

}  // namespace FastMath

#if LS_COMPILER == LS_COMPILER_CLANG
    #pragma clang diagnostic pop
#elif LS_COMPILER == LS_COMPILER_GCC
    #pragma GCC diagnostic pop
#elif LS_COMPILER == LS_COMPILER_MSVC
    #pragma warning( pop )
#endif
