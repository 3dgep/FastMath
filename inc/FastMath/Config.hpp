#pragma once

// Compiler detection.
#define FM_COMPILER_CLANG ( 1 << 0 )
#define FM_COMPILER_GCC   ( 1 << 1 )
#define FM_COMPILER_MSVC  ( 1 << 2 )

#if defined( __clang__ )
    #define FM_COMPILER FM_COMPILER_CLANG
#elif defined( __GNUC__ ) || defined( __MINGW32__ )
    #define FM_COMPILER FM_COMPILER_GCC
#elif defined( _MSC_VER )
    #define FM_COMPILER FM_COMPILER_MSVC
#endif

// Configuration for depth control and handedness.
#define FM_NEGATIVE_ONE_TO_ONE ( 1 << 0 )  // -1 <= z_ndc <= 1
#define FM_ZERO_TO_ONE         ( 1 << 1 )  // 0 <= z_ndc <= 1
#define FM_LEFT_HANDED         ( 1 << 2 )  // Left-handed coordinate system.
#define FM_RIGHT_HANDED        ( 1 << 3 )  // Right-handed coordinate system.

#if !defined( FM_DEPTH_RANGE )
    #define FM_DEPTH_RANGE FM_ZERO_TO_ONE  // Use 0..1 By default.
#endif
#if !defined( FM_HANDEDNESS )
    #define FM_HANDEDNESS FM_LEFT_HANDED  // Use a left-handed coordinate system by default.
#endif

#if !defined( FM_DISABLE_INTRINSICS )
    #if defined( __AVX2__ ) && !defined( FM_AVX2 )
        #define FM_AVX2
        #include <immintrin.h>
    #endif

    #if defined( __AVX__ ) && !defined( FM_AVX )
        #define FM_AVX
        #include <immintrin.h>
    #endif

    #if defined( __SSE4_1__ ) || defined( __AVX__ ) && !defined( FM_SSE4 )
        #define FM_SSE4
        #include <smmintrin.h>
    #endif

    #if defined( __SSE3__ ) || defined( __AVX__ ) && !defined( FM_SSE3 )
        #define FM_SSE3
        #include <pmmintrin.h>
    #endif

    #if defined( __SSE2__ ) || defined( _M_X64 ) && !defined( FM_SSE2 )
        #define FM_SSE2
        #include <emmintrin.h>
    #endif

    #if defined( __SSE__ ) || defined( _M_X64 ) && !defined( FM_SSE )
        #define FM_SSE
        #include <xmmintrin.h>
    #endif
#endif