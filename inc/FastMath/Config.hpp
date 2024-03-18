#pragma once

#define LS_COMPILER_CLANG ( 1 << 0 )
#define LS_COMPILER_GCC   ( 1 << 1 )
#define LS_COMPILER_MSVC  ( 1 << 2 )

#if defined( __clang__ )
    #define LS_COMPILER LS_COMPILER_CLANG
#elif defined( __GNUC__ ) || defined( __MINGW32__ )
    #define LS_COMPILER LS_COMPILER_GCC
#elif defined( _MSC_VER )
    #define LS_COMPILER LS_COMPILER_MSVC
#endif

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

#if LS_COMPILER == LS_COMPILER_CLANG
    #pragma clang diagnostic pop
#elif LS_COMPILER == LS_COMPILER_GCC
    #pragma GCC diagnostic pop
#elif LS_COMPILER == LS_COMPILER_MSVC
    #pragma warning( pop )
#endif

// Configuration for depth control and handedness.
#define LS_NEGATIVE_ONE_TO_ONE ( 1 << 0 )  // -1 <= z_ndc <= 1
#define LS_ZERO_TO_ONE         ( 1 << 1 )  // 0 <= z_ndc <= 1
#define LS_LEFT_HANDED         ( 1 << 2 )  // Left-handed coordinate system.
#define LS_RIGHT_HANDED        ( 1 << 3 )  // Right-handed coordinate system.

#if !defined( LS_DEPTH_RANGE )
    #define LS_DEPTH_RANGE LS_ZERO_TO_ONE  // Use 0..1 By default.
#endif
#if !defined( LS_HANDEDNESS )
    #define LS_HANDEDNESS LS_LEFT_HANDED  // Use a left-handed coordinate system by default.
#endif

#if !defined( LS_DISABLE_INTRINSICS )
    #if defined( __AVX2__ ) && !defined( LS_AVX2 )
        #define LS_AVX2
        #include <immintrin.h>
    #endif

    #if defined( __AVX__ ) && !defined( LS_AVX )
        #define LS_AVX
        #include <immintrin.h>
    #endif

    #if defined( __SSE4_1__ ) || defined( __AVX__ ) && !defined( LS_SSE4 )
        #define LS_SSE4
        #include <smmintrin.h>
    #endif

    #if defined( __SSE3__ ) || defined( __AVX__ ) && !defined( LS_SSE3 )
        #define LS_SSE3
        #include <pmmintrin.h>
    #endif

    #if defined( __SSE2__ ) || defined( _M_X64 ) && !defined( LS_SSE2 )
        #define LS_SSE2
        #include <emmintrin.h>
    #endif

    #if defined( __SSE__ ) || defined( _M_X64 ) && !defined( LS_SSE )
        #define LS_SSE
        #include <xmmintrin.h>
    #endif
#endif