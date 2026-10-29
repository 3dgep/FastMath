#include <FastMath/Matrix.hpp>
#include <FastMath/Quaternion.hpp>
#include <FastMath/Vector.hpp>
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// The inputs are passed through benchmark::DoNotOptimize on every iteration
// so that the compiler can't compute the result at compile time.

static void Matrix4_Multiply_FastMath( benchmark::State& state )
{
    FastMath::Matrix4f a { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    FastMath::Matrix4f b { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        FastMath::Matrix4f c = a * b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Matrix4_Multiply_FastMath );

static void Matrix4_Multiply_GLM( benchmark::State& state )
{
    glm::mat4 a { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    glm::mat4 b { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        glm::mat4 c = a * b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Matrix4_Multiply_GLM );

static void Matrix4_Vector4_FastMath( benchmark::State& state )
{
    FastMath::Matrix4f m { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    FastMath::Vector4f v { 1, 2, 3, 4 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        benchmark::DoNotOptimize( v );
        FastMath::Vector4f r = m * v;
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Vector4_FastMath );

static void Matrix4_Vector4_GLM( benchmark::State& state )
{
    glm::mat4 m { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    glm::vec4 v { 1, 2, 3, 4 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        benchmark::DoNotOptimize( v );
        glm::vec4 r = m * v;
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Vector4_GLM );

static void Matrix4_Transpose_FastMath( benchmark::State& state )
{
    FastMath::Matrix4f m { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        FastMath::Matrix4f r = transpose( m );
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Transpose_FastMath );

static void Matrix4_Transpose_GLM( benchmark::State& state )
{
    glm::mat4 m { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        glm::mat4 r = glm::transpose( m );
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Transpose_GLM );

static void Matrix4_Inverse_FastMath( benchmark::State& state )
{
    FastMath::Matrix4f m { 2, 0, 0, 1, 0, 3, 0, 2, 0, 0, 4, 3, 0, 0, 0, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        FastMath::Matrix4f r = inverse( m );
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Inverse_FastMath );

static void Matrix4_Inverse_GLM( benchmark::State& state )
{
    glm::mat4 m { 2, 0, 0, 1, 0, 3, 0, 2, 0, 0, 4, 3, 0, 0, 0, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( m );
        glm::mat4 r = glm::inverse( m );
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Matrix4_Inverse_GLM );

static void Quaternion_Multiply_FastMath( benchmark::State& state )
{
    FastMath::quat a { 0.5f, 0.5f, 0.5f, 0.5f };
    FastMath::quat b { 0.0f, 0.0f, 0.0f, 1.0f };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        FastMath::quat c = a * b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Quaternion_Multiply_FastMath );

static void Quaternion_Multiply_GLM( benchmark::State& state )
{
    glm::quat a { 0.5f, 0.5f, 0.5f, 0.5f };
    glm::quat b { 0.0f, 0.0f, 0.0f, 1.0f };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        glm::quat c = a * b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Quaternion_Multiply_GLM );

static void Quaternion_Rotate_FastMath( benchmark::State& state )
{
    FastMath::quat     q { 0.5f, 0.5f, 0.5f, 0.5f };
    FastMath::Vector3f v { 1, 2, 3 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( q );
        benchmark::DoNotOptimize( v );
        FastMath::Vector3f r = q * v;
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Quaternion_Rotate_FastMath );

static void Quaternion_Rotate_GLM( benchmark::State& state )
{
    glm::quat q { 0.5f, 0.5f, 0.5f, 0.5f };
    glm::vec3 v { 1, 2, 3 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( q );
        benchmark::DoNotOptimize( v );
        glm::vec3 r = q * v;
        benchmark::DoNotOptimize( r );
    }
}
BENCHMARK( Quaternion_Rotate_GLM );

static void Vector3_Cross_FastMath( benchmark::State& state )
{
    FastMath::Vector3f a { 1, 2, 3 };
    FastMath::Vector3f b { 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        FastMath::Vector3f c = cross( a, b );
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector3_Cross_FastMath );

static void Vector3_Cross_GLM( benchmark::State& state )
{
    glm::vec3 a { 1, 2, 3 };
    glm::vec3 b { 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        glm::vec3 c = glm::cross( a, b );
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector3_Cross_GLM );

static void Vector3_Normalize_FastMath( benchmark::State& state )
{
    FastMath::Vector3f a { 1, 2, 3 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        FastMath::Vector3f c = normalize( a );
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector3_Normalize_FastMath );

static void Vector3_Normalize_GLM( benchmark::State& state )
{
    glm::vec3 a { 1, 2, 3 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        glm::vec3 c = glm::normalize( a );
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector3_Normalize_GLM );

static void Vector4_Add_FastMath( benchmark::State& state )
{
    FastMath::Vector4f a { 1, 2, 3, 4 };
    FastMath::Vector4f b { 4, 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        FastMath::Vector4f c = a + b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector4_Add_FastMath );

static void Vector4_Add_GLM( benchmark::State& state )
{
    glm::vec4 a { 1, 2, 3, 4 };
    glm::vec4 b { 4, 3, 2, 1 };

    for ( auto _: state )
    {
        benchmark::DoNotOptimize( a );
        benchmark::DoNotOptimize( b );
        glm::vec4 c = a + b;
        benchmark::DoNotOptimize( c );
    }
}
BENCHMARK( Vector4_Add_GLM );
