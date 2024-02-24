#include <LightSpeed/Math/Vector.hpp>
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>

union vec
{
    float  f[4];
    __m128 v;
};

const vec a = { 1, 2, 3, 4 };
const vec b = { 1, 2, 3, 4 };

static void Vector_Dot_NoSSE( benchmark::State& state )
{
    vec res;
    for ( auto _: state )
    {
        for ( int i = 0; i < 4; ++i )
            res.f[i] = a.f[i] * b.f[i];

        res.f[0] = res.f[0] + res.f[1] + res.f[2] + res.f[3];

        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_NoSSE );

static void Vector_Dot_SSE2( benchmark::State& state )
{
    vec res;
    for ( auto _: state )
    {
        vec tmp;
        tmp.v = _mm_mul_ps( a.v, b.v );
        res.v = _mm_shuffle_ps( tmp.v, tmp.v, _MM_SHUFFLE( 0, 0, 3, 2 ) );
        tmp.v = _mm_add_ps( tmp.v, res.v );
        res.v = _mm_shuffle_ps( tmp.v, tmp.v, _MM_SHUFFLE( 0, 0, 0, 1 ) );
        res.v = _mm_add_ss( res.v, tmp.v );

        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_SSE2 );

static void Vector_Dot_SSE3( benchmark::State& state )
{
    vec res;
    for ( auto _: state )
    {
        res.v = _mm_mul_ps( a.v, b.v );
        res.v = _mm_hadd_ps( res.v, res.v );
        res.v = _mm_hadd_ps( res.v, res.v );

        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_SSE3 );

static void Vector_Dot_SSE4( benchmark::State& state )
{
    vec res;
    for ( auto _: state )
    {
        res.v = _mm_dp_ps( a.v, b.v, 0xff );
        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_SSE4 );

static void Vector_Dot_GLM( benchmark::State& state )
{
    const glm::vec4 a = { 1, 2, 3, 4 };
    const glm::vec4 b = { 1, 2, 3, 4 };

    float res;

    for ( auto _: state )
    {
        res = glm::dot( a, b );
        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_GLM );

static void Vector_Dot_LightSpeed( benchmark::State& state )
{
    const ls::Vector4f a = { 1, 3, 4, 4 };
    const ls::Vector4f b = { 1, 2, 3, 4 };

    float res;
    for ( auto _: state )
    {
        res = ls::dot( a, b );
        benchmark::DoNotOptimize( res );
    }
}
BENCHMARK( Vector_Dot_LightSpeed );