// ReSharper disable CppLocalVariableMayBeConst
#include <FastMath/Common.hpp>
#include <FastMath/Vector.hpp>

#include <array>
#include <gtest/gtest.h>

using namespace FastMath;

TEST( Vector, DefaultConstruct )
{
    Vector4f v;

    ASSERT_EQ( 0.0f, v.x );
    ASSERT_EQ( 0.0f, v.y );
    ASSERT_EQ( 0.0f, v.z );
    ASSERT_EQ( 0.0f, v.w );
}

TEST( Vector, SingleValueConstructor )
{
    Vector4f a { 1 };

    ASSERT_EQ( 1.0f, a.x );
    ASSERT_EQ( 1.0f, a.y );
    ASSERT_EQ( 1.0f, a.z );
    ASSERT_EQ( 1.0f, a.w );
}

TEST( Vector, UNIT_X )
{
    const auto v = Vector4f::UNIT_X;

    ASSERT_EQ( 1.0f, v.x );
    ASSERT_EQ( 0.0f, v.y );
    ASSERT_EQ( 0.0f, v.z );
    ASSERT_EQ( 0.0f, v.w );
}

TEST( Vector, UNIT_Y )
{
    auto v = Vector4f::UNIT_Y;

    ASSERT_EQ( 0.0f, v.x );
    ASSERT_EQ( 1.0f, v.y );
    ASSERT_EQ( 0.0f, v.z );
    ASSERT_EQ( 0.0f, v.w );
}

TEST( Vector, UNIT_Z )
{
    auto v = Vector4f::UNIT_Z;

    ASSERT_EQ( 0.0f, v.x );
    ASSERT_EQ( 0.0f, v.y );
    ASSERT_EQ( 1.0f, v.z );
    ASSERT_EQ( 0.0f, v.w );
}

TEST( Vector, UNIT_W )
{
    auto v = Vector4f::UNIT_W;

    ASSERT_EQ( 0.0f, v.x );
    ASSERT_EQ( 0.0f, v.y );
    ASSERT_EQ( 0.0f, v.z );
    ASSERT_EQ( 1.0f, v.w );
}

TEST( Vector, InitializerList )
{
    Vector4f v = { 1, 2, 3, 4 };

    ASSERT_EQ( 1.0f, v.x );
    ASSERT_EQ( 2.0f, v.y );
    ASSERT_EQ( 3.0f, v.z );
    ASSERT_EQ( 4.0f, v.w );
}

TEST( Vector, Span )
{
    float a[] = { 1, 2, 3, 4 };

    Vector4f v = std::span { a };

    ASSERT_EQ( 1.0f, v.x );
    ASSERT_EQ( 2.0f, v.y );
    ASSERT_EQ( 3.0f, v.z );
    ASSERT_EQ( 4.0f, v.w );
}

TEST( Vector, CopyConstructor )
{
    Vector4f a { 1, 2, 3, 4 };
    Vector4f b { a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, Vector2_to_Vector3 )
{
    Vector2f a { 1, 2 };
    Vector3f b { a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 0.0f, b.z );
}

TEST( Vector, Vector2_to_Vector4 )
{
    Vector2f a { 1, 2 };
    Vector4f b { a, 3, 4 };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, Vector3_to_Vector2 )
{
    Vector3f a { 1, 2, 3 };
    Vector2f b { a, 3, 4 };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
}

TEST( Vector, Vector2_to_f2Vector4 )
{
    Vector2f a { 3, 4 };
    Vector4f b { 1, 2, a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, xVector3 )
{
    Vector3f a { 2, 3, 4 };
    Vector4f b { 1, a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, xyVector2 )
{
    Vector2f a { 3, 4 };
    Vector4f b { 1, 2, a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, xyzVector1 )
{
    Vector<float, 1> a { 4 };
    Vector4f         b { 1, 2, 3, a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, xyzwVector )
{
    Vector2f a { 5, 6 };
    Vector4f b { 1, 2, 3, 4, a };

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
    ASSERT_EQ( 3.0f, b.z );
    ASSERT_EQ( 4.0f, b.w );
}

TEST( Vector, Assignment )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    b = a;

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
}

TEST( Vector, Unary_Plus )
{
    Vector2f a { 1, 2 };
    Vector2f b = +a;

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
}

TEST( Vector, Unary_Minus )
{
    Vector2f a { 1, 2 };
    Vector2f b = -a;

    ASSERT_EQ( -1.0f, b.x );
    ASSERT_EQ( -2.0f, b.y );
}

TEST( Vector, Addition )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    Vector2f c = a + b;

    ASSERT_EQ( 4.0f, c.x );
    ASSERT_EQ( 6.0f, c.y );
}

TEST( Vector, Addition_Assignment )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    b += a;

    ASSERT_EQ( 4.0f, b.x );
    ASSERT_EQ( 6.0f, b.y );
}

TEST( Vector, Subtraction )
{
    Vector2f a { 3, 4 };
    Vector2f b { 1, 2 };

    Vector2f c = a - b;

    ASSERT_EQ( 2.0f, c.x );
    ASSERT_EQ( 2.0f, c.y );
}

TEST( Vector, Subtraction_Assignment )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    b -= a;

    ASSERT_EQ( 2.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
}

TEST( Vector, Multiplication )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    Vector2f c = a * b;

    ASSERT_EQ( 3.0f, c.x );
    ASSERT_EQ( 8.0f, c.y );
}

TEST( Vector, Scalar_Multiplication )
{
    Vector2f a { 1, 2 };

    Vector2f b = a * 2;

    ASSERT_EQ( 2.0f, b.x );
    ASSERT_EQ( 4.0f, b.y );
}

TEST( Vector, Scalar_Multiplication_Assignment )
{
    Vector2f a { 1, 2 };
    Vector2f b { 2, 4 };

    a *= 2;

    ASSERT_EQ( a, b );
}

TEST( Vector, Scalar_Division )
{
    Vector2f a { 2, 4 };

    Vector2f b = a / 2;

    ASSERT_EQ( 1.0f, b.x );
    ASSERT_EQ( 2.0f, b.y );
}

TEST( Vector, Scalar_Division_Assignment )
{
    Vector2f a { 2, 4 };

    a /= 2;

    ASSERT_EQ( 1.0f, a.x );
    ASSERT_EQ( 2.0f, a.y );
}

TEST( Vector, Equality )
{
    Vector2f a { 1, 2 };
    Vector2f b { 1, 2 };

    ASSERT_EQ( a, b );
}

TEST( Vector, Inequality )
{
    Vector2f a { 1, 2 };
    Vector2f b { 3, 4 };

    ASSERT_NE( a, b );
}

TEST( Vector, Less_Than )
{
    Vector2f a { 1, 2 };
    Vector2f b { 1, 3 };

    ASSERT_LT( a, b );
}

TEST( Vector, Greater_Than )
{
    Vector2f a { 3, 4 };
    Vector2f b { 1, 2 };

    ASSERT_GT( a, b );
}

TEST( Vector, Degrees )
{
    Vector2f rad { PI_OVER_TWO<float>, PI<float> };
    Vector2f deg = degrees( rad );

    ASSERT_EQ( 90.0f, deg.x );
    ASSERT_EQ( 180.0f, deg.y );
}

TEST( Vector, Radians )
{
    Vector2f deg { 90.0f, 180.0f };
    Vector2f rad = radians( deg );

    ASSERT_EQ( PI_OVER_TWO<float>, rad.x );
    ASSERT_EQ( PI<float>, rad.y );
}

TEST( Vector, Cosine )
{
    Vector2f a { 0.0f, PI_OVER_TWO<float> };
    auto     b = cos( a );

    ASSERT_FLOAT_EQ( 1.0f, b.x );
    // ASSERT_FLOAT_EQ( 0.0f, b.y );
    ASSERT_NEAR( 0.0f, b.y, 4.5e-8 );  // Cosine is really not that accurate (apparently).
}

TEST( Vector, Sine )
{
    Vector2f a { 0.0f, PI_OVER_TWO<float> };
    auto     b = sin( a );

    ASSERT_FLOAT_EQ( 0.0f, b.x );
    ASSERT_FLOAT_EQ( 1.0f, b.y );
}

TEST( Vector, Tangent )
{
    Vector2f a { 0.0f, PI<float> };
    Vector2f b = tan( a );

    ASSERT_FLOAT_EQ( 0.0f, b.x );
    // ASSERT_FLOAT_EQ( 0.0f, b.y );
    ASSERT_NEAR( 0.0, b.y, 8.8e-8 );  // Tan is even less accurate (apparently).
}

TEST( Vector, Equal )
{
    Vector2f a { 0 };
    Vector2f b { 0 };

    ASSERT_TRUE( all( equal( a, b ) ) );
}

TEST( Vector, IsNormalized)
{
    Vector4f a{ 13, 25, -300, 1 };
    Vector4f b = normalize( a );

    ASSERT_TRUE( isNormalized( b ) );
}

TEST( Vector, IsNotNormalized)
{
    Vector4f a { 1, 1, 0, 0 };

    ASSERT_FALSE( isNormalized( a ) );
}