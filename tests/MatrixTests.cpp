#include <gtest/gtest.h>

#include <FastMath/Matrix.hpp>

using namespace FastMath;

TEST( Matrix, IDENTITY )
{
    Matrix4f I = Matrix4f::IDENTITY;

    for ( int i = 0; i < 4; ++i )
        for ( int j = 0; j < 4; ++j )
        {
            if ( i != j )
                ASSERT_EQ( I[i][j], 0.0f );
            else
                ASSERT_EQ( I[i][j], 1.0f );
        }
}

TEST( Matrix, Default_Constructor )
{
    Matrix2f a;

    ASSERT_EQ( a.X.x, 0.0f );
    ASSERT_EQ( a.X.y, 0.0f );
    ASSERT_EQ( a.Y.x, 0.0f );
    ASSERT_EQ( a.Y.y, 0.0f );
}

TEST( Matrix, Index_Operator )
{
    Matrix2f a = { { 1, 2 }, { 3, 4 } };

    ASSERT_EQ( a[0][0], 1.0f );
    ASSERT_EQ( a[0][1], 2.0f );
    ASSERT_EQ( a[1][0], 3.0f );
    ASSERT_EQ( a[1][1], 4.0f );
}

TEST( Matrix, Copy_Constructor )
{
    Matrix2f a = { { 1, 2 }, { 3, 4 } };
    Matrix2f b = { a };

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 3.0f );
    ASSERT_EQ( b[1][1], 4.0f );
}

TEST( Matrix, Copy_Constructor2 )
{
    Matrix<int, 4, 3> a { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };
    Matrix2f          b { a };

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 4.0f );
    ASSERT_EQ( b[1][1], 5.0f );
}

TEST( Matrix, Copy_Constructor3 )
{
    Matrix2f a { 1, 2, 3, 4 };
    Matrix4f b { a };

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 3.0f );
    ASSERT_EQ( b[1][1], 4.0f );
}

TEST( Matrix, Vector_Initializer )
{
    Matrix3f a { Vector3f::UNIT_X, Vector3f::UNIT_Y, Vector3f::UNIT_Z };

    ASSERT_EQ( a[0][0], 1.0f );
    ASSERT_EQ( a[1][1], 1.0f );
    ASSERT_EQ( a[2][2], 1.0f );
}

TEST( Matrix, Assignmnet )
{
    Matrix2f a { 1, 2, 3, 4 };
    Matrix4f b;

    b = a;

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 3.0f );
    ASSERT_EQ( b[1][1], 4.0f );
}

TEST( Matrix, Assignmnet2 )
{
    Matrix3f a { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix2f b;

    b = a;

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 4.0f );
    ASSERT_EQ( b[1][1], 5.0f );
}

TEST( Matrix, Unary_Plus )
{
    Matrix2f a { 1, 2, 3, 4 };

    Matrix2f b { +a };

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 3.0f );
    ASSERT_EQ( b[1][1], 4.0f );
}

TEST( Matrix, Unary_Minus )
{
    Matrix2f a { 1, 2, 3, 4 };

    Matrix2f b { -a };

    ASSERT_EQ( b[0][0], -1.0f );
    ASSERT_EQ( b[0][1], -2.0f );
    ASSERT_EQ( b[1][0], -3.0f );
    ASSERT_EQ( b[1][1], -4.0f );
}

TEST( Matrix, Addition )
{
    Matrix2f a { 1, 2, 3, 4 };
    Matrix2f b { 5, 6, 7, 8 };

    Matrix2f c { a + b };

    ASSERT_EQ( c[0][0], 6.0f );
    ASSERT_EQ( c[0][1], 8.0f );
    ASSERT_EQ( c[1][0], 10.0f );
    ASSERT_EQ( c[1][1], 12.0f );
}

TEST( Matrix, Addition_Assignment )
{
    Matrix2f a { 1, 2, 3, 4 };
    Matrix2f b { 5, 6, 7, 8 };

    a += b;

    ASSERT_EQ( a[0][0], 6.0f );
    ASSERT_EQ( a[0][1], 8.0f );
    ASSERT_EQ( a[1][0], 10.0f );
    ASSERT_EQ( a[1][1], 12.0f );
}

TEST( Matrix, Subtraction )
{
    Matrix2f a { 5, 6, 7, 8 };
    Matrix2f b { 1, 2, 3, 4 };

    Matrix2f c { a - b };

    ASSERT_EQ( c[0][0], 4.0f );
    ASSERT_EQ( c[0][1], 4.0f );
    ASSERT_EQ( c[1][0], 4.0f );
    ASSERT_EQ( c[1][1], 4.0f );
}

TEST( Matrix, Subtraction_Assignment )
{
    Matrix2f a { 1, 2, 3, 4 };
    Matrix2f b { 5, 6, 7, 8 };

    a -= b;

    ASSERT_EQ( a[0][0], -4.0f );
    ASSERT_EQ( a[0][1], -4.0f );
    ASSERT_EQ( a[1][0], -4.0f );
    ASSERT_EQ( a[1][1], -4.0f );
}

TEST( Matrix, Scalar_Multiplication )
{
    Matrix2f a { 1, 2, 3, 4 };

    Matrix2f b { a * 2 };

    ASSERT_EQ( b[0][0], 2.0f );
    ASSERT_EQ( b[0][1], 4.0f );
    ASSERT_EQ( b[1][0], 6.0f );
    ASSERT_EQ( b[1][1], 8.0f );
}

TEST( Matrix, Scalar_Multiplication2 )
{
    Matrix2f a { 1, 2, 3, 4 };

    Matrix2f b { 2 * a };

    ASSERT_EQ( b[0][0], 2.0f );
    ASSERT_EQ( b[0][1], 4.0f );
    ASSERT_EQ( b[1][0], 6.0f );
    ASSERT_EQ( b[1][1], 8.0f );
}

TEST( Matrix, Scalar_Multiplication_Assignment )
{
    Matrix2f a { 1, 2, 3, 4 };

    a *= 2;

    ASSERT_EQ( a[0][0], 2.0f );
    ASSERT_EQ( a[0][1], 4.0f );
    ASSERT_EQ( a[1][0], 6.0f );
    ASSERT_EQ( a[1][1], 8.0f );
}

TEST( Matrix, Vector_Multiplication )
{
    Matrix2f a { 1, 2, 3, 4 };
    Vector2f v { 1, 2 };

    Vector2f b = a * v;

    ASSERT_EQ( b[0], 5.0f );
    ASSERT_EQ( b[1], 11.0f );
}

TEST( Matrix, Vector_Multiplication2 )
{
    float2x3 a = { { 1, 2, 3 }, { 4, 5, 6 } };
    float3   v = { 1, 2, 3 };

    Vector2f b = a * v;

    ASSERT_EQ( b[0], 14.0f );
    ASSERT_EQ( b[1], 32.0f );
}

TEST( Matrix, Vector_PostMultiply )
{
    float3x2 a = float3x2::IDENTITY;
    float3   v = { 1, 2, 3 };

    float2 b = v * a;

    ASSERT_EQ( b.x, 1.0f );
    ASSERT_EQ( b.y, 2.0f );
}

TEST( Matrix, Vector_PostMultiply2 )
{
    Matrix<float, 3, 2> a = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    Vector3f            v = { 1, 2, 3 };

    Vector2f b = v * a;

    ASSERT_EQ( b.x, 22.0f );
    ASSERT_EQ( b.y, 28.0f );
}

TEST( Matrix, Transpose )
{
    Matrix3f a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix3f b = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };

    a = transpose( a );

    ASSERT_EQ( a, b );
}

TEST( Matrix, Transpose2 )
{
    float2x3 a = { { 1, 2, 3 }, { 4, 5, 6 } };

    float3x2 b = transpose( a );

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 4.0f );
    ASSERT_EQ( b[1][0], 2.0f );
    ASSERT_EQ( b[1][1], 5.0f );
    ASSERT_EQ( b[2][0], 3.0f );
    ASSERT_EQ( b[2][1], 6.0f );
}

TEST( Matrix, Transpose3 )
{
    Matrix<float, 1, 3> a = { { 1, 2, 3 } };

    Matrix<float, 3, 1> b = transpose( a );

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[1][0], 2.0f );
    ASSERT_EQ( b[2][0], 3.0f );
}

TEST( Matrix, SubMatrix0 )
{
    Matrix3f a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix2f b = Matrix2f( a, 0, 0 );

    ASSERT_EQ( b[0][0], 5.0f );
    ASSERT_EQ( b[0][1], 6.0f );
    ASSERT_EQ( b[1][0], 8.0f );
    ASSERT_EQ( b[1][1], 9.0f );
}

TEST( Matrix, SubMatrix1 )
{
    Matrix3f a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix2f b = Matrix2f( a, 1, 1 );

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 3.0f );
    ASSERT_EQ( b[1][0], 7.0f );
    ASSERT_EQ( b[1][1], 9.0f );
}

TEST( Matrix, SubMatrix2 )
{
    Matrix3f a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Matrix2f b = Matrix2f( a, 2, 2 );

    ASSERT_EQ( b[0][0], 1.0f );
    ASSERT_EQ( b[0][1], 2.0f );
    ASSERT_EQ( b[1][0], 4.0f );
    ASSERT_EQ( b[1][1], 5.0f );
}

TEST( Matrix, SubMatrix3 )
{
    Matrix2f a = { { 1, 2 }, { 3, 4 } };
    Matrix4f b = a;
    Matrix4f c = { { 1, 2, 0, 0 }, { 3, 4, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

    ASSERT_EQ( c, b );
}

TEST( Matrix, Matrix_Determinate )
{
    Matrix3f a   = Matrix3f::IDENTITY;
    float    det = determinant( a );

    ASSERT_EQ( det, 1.0f );
}
TEST( Matrix, Matrix_Determinate2 )
{
    Matrix3f a   = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    float    det = determinant( a );

    ASSERT_EQ( det, 0.0f );
}

TEST( Matrix, Matrix_Inverse )
{
    auto a = Matrix4f::IDENTITY;

    // The inverse of the identity matrix is always the identity matrix.
    auto a_inv = inverse( a );

    ASSERT_EQ( a, a_inv );
}

TEST( Matrix, Matrix_Inverse2 )
{
    // Inverse of a 2x2 matrix.
    Matrix2f a = { { 2, 3 }, { 2, 2 } };
    Matrix2f b = { { -1.0f, 3.0f / 2.0f }, { 1.0f, -1.0f } };

    a = inverse( a );

    ASSERT_EQ( a, b );
}

TEST( Matrix, Matrix_Inverse3 )
{
    // Inverse of a 3x3 matrix.
    Matrix3f a = { { 1, 2, 3 }, { 3, 2, 1 }, { 2, 1, 3 } };
    Matrix3f b = { { -5.0f / 12.0f, 1.0f / 4.0f, 1.0f / 3.0f },
                   { 7.0f / 12.0f, 1.0f / 4.0f, -2.0f / 3.0f },
                   { 1.0f / 12.0f, -1.0f / 4.0f, 1.0f / 3.0f } };

    a = inverse( a );

    for ( int i = 0; i < 9; ++i )
    {
        ASSERT_FLOAT_EQ( a.m[i], b.m[i] );
    }
}

TEST( Matrix, Matrix_Inverse4 )
{
    Matrix3d a = { { 1, 2, 3 }, { 3, 2, 1 }, { 2, 1, 3 } };
    Matrix3d b = Matrix3d::IDENTITY;

    // Multiplying a matrix by it's inverse results in the Identity matrix.
    auto a_inv = inverse( a );
    auto I     = a * a_inv;

    for ( int i = 0; i < 9; ++i )
    {
        // Close enough...
        EXPECT_NEAR( I.m[i], b.m[i], 1e-15 );
    }
}

TEST( Matrix, Translate_Vector3 )
{
    Vector3f v = { 1, 2, 3 };
    Matrix4f a = translate( v );

    ASSERT_EQ( a[0][3], v[0] );
    ASSERT_EQ( a[1][3], v[1] );
    ASSERT_EQ( a[2][3], v[2] );
    ASSERT_EQ( a[3][3], 1.0f );
}

TEST( Matrix, FrustumLH01 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = frustumLH01( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, FrustumLH11 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = frustumLH11( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f lbf { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * lbf;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, FrustumRH01 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = frustumRH01( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f lbf { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * lbf;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, FrustumRH11 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = frustumRH11( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, OrthographicLH01 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = orthographicLH01( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, OrthographicLH11 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = orthographicLH11( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, OrthographicRH01 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = orthographicRH01( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f lbf { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * lbf;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, OrthographicRH11 )
{
    float left   = -100;
    float right  = 100;
    float bottom = -100;
    float top    = 100;
    float near   = 1;
    float far    = 100;

    auto m = orthographicRH11( left, right, bottom, top, near, far );

    {
        Vector4f lbn { left, bottom, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn { right, bottom, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn { left, top, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn { right, top, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f lbf { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * lbf;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveFoVLH01 )
{
    float fovy        = radians( 60.0f );
    float aspectRatio = 16.0f / 9.0f;
    float near        = 1.0f;
    float far         = 1000.0f;

    auto m = perspectiveFoVLH01( fovy, aspectRatio, near, far );

    {
        Vector4f n    = { 0.0f, 0.0f, near, 1.0f };
        Vector4f clip = m * n;

        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveFoVLH11 )
{
    float fovy        = radians( 60.0f );
    float aspectRatio = 16.0f / 9.0f;
    float near        = 1.0f;
    float far         = 1000.0f;

    auto m = perspectiveFoVLH11( fovy, aspectRatio, near, far );

    {
        Vector4f n    = { 0.0f, 0.0f, near, 1.0f };
        Vector4f clip = m * n;

        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveFoVRH01 )
{
    float fovy        = radians( 60.0f );
    float aspectRatio = 16.0f / 9.0f;
    float near        = 1.0f;
    float far         = 1000.0f;

    auto m = perspectiveFoVRH01( fovy, aspectRatio, near, far );

    {
        Vector4f n    = { 0.0f, 0.0f, -near, 1.0f };
        Vector4f clip = m * n;

        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveFoVRH11 )
{
    float fovy        = radians( 60.0f );
    float aspectRatio = 16.0f / 9.0f;
    float near        = 1.0f;
    float far         = 1000.0f;

    auto m = perspectiveFoVRH11( fovy, aspectRatio, near, far );

    {
        Vector4f n    = { 0.0f, 0.0f, -near, 1.0f };
        Vector4f clip = m * n;

        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveLH01 )
{
    float width  = 1920.0f;
    float height = 1080.0f;
    float near   = 1.0f;
    float far    = 100.0f;

    auto m = perspectiveLH01( width, height, near, far );

    {
        Vector4f lbn  = { -width / 2.0f, -height / 2.0f, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn  = { width / 2.0f, -height / 2.0f, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn  = { -width / 2.0f, height / 2.0f, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn  = { width / 2.0f, height / 2.0f, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}
TEST( Matrix, PerspectiveLH11 )
{
    float width  = 1920.0f;
    float height = 1080.0f;
    float near   = 1.0f;
    float far    = 100.0f;

    auto m = perspectiveLH11( width, height, near, far );

    {
        Vector4f lbn  = { -width / 2.0f, -height / 2.0f, near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn  = { width / 2.0f, -height / 2.0f, near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn  = { -width / 2.0f, height / 2.0f, near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn  = { width / 2.0f, height / 2.0f, near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}
TEST( Matrix, PerspectiveRH01 )
{
    float width  = 1920.0f;
    float height = 1080.0f;
    float near   = 1.0f;
    float far    = 100.0f;

    auto m = perspectiveRH01( width, height, near, far );

    {
        Vector4f lbn  = { -width / 2.0f, -height / 2.0f, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn  = { width / 2.0f, -height / 2.0f, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn  = { -width / 2.0f, height / 2.0f, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn  = { width / 2.0f, height / 2.0f, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( 0.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, PerspectiveRH11 )
{
    float width  = 1920.0f;
    float height = 1080.0f;
    float near   = 1.0f;
    float far    = 100.0f;

    auto m = perspectiveRH11( width, height, near, far );

    {
        Vector4f lbn  = { -width / 2.0f, -height / 2.0f, -near, 1.0f };
        Vector4f clip = m * lbn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rbn  = { width / 2.0f, -height / 2.0f, -near, 1.0f };
        Vector4f clip = m * rbn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f ltn  = { -width / 2.0f, height / 2.0f, -near, 1.0f };
        Vector4f clip = m * ltn;

        ASSERT_FLOAT_EQ( -1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f rtn  = { width / 2.0f, height / 2.0f, -near, 1.0f };
        Vector4f clip = m * rtn;

        ASSERT_FLOAT_EQ( 1.0f, clip.x / clip.w );
        ASSERT_FLOAT_EQ( 1.0f, clip.y / clip.w );
        ASSERT_FLOAT_EQ( -1.0f, clip.z / clip.w );
    }
    {
        Vector4f f    = { 0.0f, 0.0f, -far, 1.0f };
        Vector4f clip = m * f;

        ASSERT_FLOAT_EQ( 1.0f, clip.z / clip.w );
    }
}

TEST( Matrix, LookAtLH )
{
    mat4 m = lookAtLH<float>( { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 } );

    ASSERT_EQ( m.X, vec4::UNIT_X );
    ASSERT_EQ( m.Y, vec4::UNIT_Y );
    ASSERT_EQ( m.Z, vec4::UNIT_Z );
    ASSERT_EQ( m.W, vec4::UNIT_W );
}

TEST( Matrix, LookAtRH )
{
    mat4 m = lookAtRH<float>( { 0, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 } );

    ASSERT_EQ( m.X, vec4::UNIT_X );
    ASSERT_EQ( m.Y, vec4::UNIT_Y );
    ASSERT_EQ( m.Z, vec4::UNIT_Z );
    ASSERT_EQ( m.W, vec4::UNIT_W );
}
