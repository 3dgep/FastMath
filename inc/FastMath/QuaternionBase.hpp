#pragma once

#include "Config.hpp"

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
template<typename T>
struct QuaternionBase
{
    constexpr QuaternionBase() noexcept;

    union
    {
        struct
        {
            T w, x, y, z;
        };
        struct
        {
            T            s;
            Vector<T, 3> vec;
        };
        T quat[4];
    };
};

template<typename T>
constexpr QuaternionBase<T>::QuaternionBase() noexcept
: quat { T( 1 ), T( 0 ), T( 0 ), T( 0 ) }
{}

#if defined( LS_SSE )
template<>
struct alignas( 16 ) QuaternionBase<float>
{
    constexpr QuaternionBase() noexcept;
    constexpr QuaternionBase( __m128 v ) noexcept;
    constexpr operator __m128() const noexcept;

    union
    {
        struct
        {
            float w, x, y, z;
        };
        struct
        {
            float            s;
            Vector<float, 3> vec;
        };
        float  quat[4];
        __m128 v;
    };
};

constexpr QuaternionBase<float>::QuaternionBase() noexcept
: quat { 1.0f, 0.0f, 0.0f, 0.0f }
{}

constexpr QuaternionBase<float>::QuaternionBase( __m128 v ) noexcept
: v { v }
{}

constexpr QuaternionBase<float>::operator __m128() const noexcept
{
    return v;
}
#endif

#if defined( LS_AVX )
template<>
struct alignas( 32 ) QuaternionBase<double>
{
    constexpr QuaternionBase() noexcept;
    constexpr QuaternionBase( __m256d v ) noexcept;
    constexpr operator __m256d() const noexcept;

    union
    {
        struct
        {
            double w, x, y, z;
        };
        struct
        {
            double            s;
            Vector<double, 3> vec;
        };
        double  quat[4];
        __m256d v;
    };
};

constexpr QuaternionBase<double>::QuaternionBase() noexcept
: quat { 1.0, 0.0, 0.0, 0.0 }
{}

constexpr QuaternionBase<double>::QuaternionBase( __m256d v ) noexcept
: v { v }
{}

constexpr QuaternionBase<double>::operator __m256d() const noexcept
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
