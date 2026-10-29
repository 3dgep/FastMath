#pragma once

#include "Config.hpp"

#if FM_COMPILER == FM_COMPILER_CLANG
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
    #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif FM_COMPILER == FM_COMPILER_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#elif FM_COMPILER == FM_COMPILER_MSVC
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

}  // namespace FastMath

#if FM_COMPILER == FM_COMPILER_CLANG
    #pragma clang diagnostic pop
#elif FM_COMPILER == FM_COMPILER_GCC
    #pragma GCC diagnostic pop
#elif FM_COMPILER == FM_COMPILER_MSVC
    #pragma warning( pop )
#endif
