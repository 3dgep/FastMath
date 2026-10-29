#include <FastMath/Quaternion.hpp>

#include <array>

#include <gtest/gtest.h>

using namespace FastMath;

TEST( Quaternion, DefaultConstruct )
{
    quat q;

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 0.0f, q.x );
    ASSERT_EQ( 0.0f, q.y );
    ASSERT_EQ( 0.0f, q.z );
}

TEST( Quaternion, ParameterizedConstructor )
{
    quat q { 1, 2, 3, 4 };

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 2.0f, q.x );
    ASSERT_EQ( 3.0f, q.y );
    ASSERT_EQ( 4.0f, q.z );
}

TEST( Quaternion, Vector3_ScalarConstructor )
{
    vec3 v { 2, 3, 4 };
    quat q { 1, v };

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 2.0f, q.x );
    ASSERT_EQ( 3.0f, q.y );
    ASSERT_EQ( 4.0f, q.z );
}

TEST( Quaternion, Mat3_Constructor )
{
    mat3 m = mat3::IDENTITY;
    quat q { m };

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 0.0f, q.x );
    ASSERT_EQ( 0.0f, q.y );
    ASSERT_EQ( 0.0f, q.z );
}

TEST( Quaternion, Mat4_Constructor )
{
    mat4 m = mat4::IDENTITY;
    quat q { m };

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 0.0f, q.x );
    ASSERT_EQ( 0.0f, q.y );
    ASSERT_EQ( 0.0f, q.z );
}

TEST( Quaternion, CopyConstructor )
{
    quat q1 { 1, 2, 3, 4 };
    quat q2 { q1 };

    ASSERT_EQ( 1.0f, q2.w );
    ASSERT_EQ( 2.0f, q2.x );
    ASSERT_EQ( 3.0f, q2.y );
    ASSERT_EQ( 4.0f, q2.z );
}

TEST( Quaternion, EulerAnglesPitch )
{
    const vec3 eulerAngles { 90.0f, 0.0f, 0.0f };
    quat       q0 { radians( eulerAngles ) };
    quat       q1 = axisAngle( vec3::UNIT_X, radians( 90.0f ) );

    ASSERT_EQ( q0, q1 );
}

TEST( Quaternion, EulerAnglesYaw )
{
    const vec3 eulerAngles { 0.0f, 90.0f, 0.0f };
    quat       q0 { radians( eulerAngles ) };
    quat       q1 = axisAngle( vec3::UNIT_Y, radians( 90.0f ) );

    ASSERT_EQ( q0, q1 );
}

TEST( Quaternion, EulerAnglesRoll )
{
    const vec3 eulerAngles { 0.0f, 0.0f, 90.0f };
    quat       q0 { radians( eulerAngles ) };
    quat       q1 = axisAngle( vec3::UNIT_Z, radians( 90.0f ) );

    ASSERT_EQ( q0, q1 );
}

TEST( Quaternion, Pitch )
{
    const vec3  eulerAngles = radians( vec3 { 90.0f, 0.0f, 0.0f } );
    quat        q { eulerAngles };
    const float pitch = FastMath::pitch( q );

    ASSERT_FLOAT_EQ( eulerAngles.x, pitch );
}

TEST( Quaternion, Yaw )
{
    vec3  eulerAngles = radians( vec3 { 0.0f, 90.0f, 0.0f } );
    quat  q { eulerAngles };
    float yaw = FastMath::yaw( q );

    ASSERT_NEAR( eulerAngles.y, yaw, 1e-3f ); // Not even close.
}

TEST( Quaternion, Roll )
{
    vec3  eulerAngles = radians( vec3 { 0.0f, 0.0f, 90.0f } );
    quat  q { eulerAngles };
    float roll = FastMath::roll( q );

    ASSERT_FLOAT_EQ( eulerAngles.z, roll );
}

TEST( Quaternion, fromTwoVectors )
{
    quat q0 { vec3::UNIT_X, vec3::UNIT_Y };
    quat q1 = axisAngle( vec3::UNIT_Z, radians( 90.0f ) );

    ASSERT_EQ( q0, q1 );
}
TEST( Quaternion, AssignmentOperator )
{
    quat q1 { 1, 2, 3, 4 };
    quat q2;

    q2 = q1;

    ASSERT_EQ( q1, q2 );
}

TEST( Quaternion, fromMat3 )
{
    mat3 m = mat3::IDENTITY;
    quat q = fromMat3( m );

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 0.0f, q.x );
    ASSERT_EQ( 0.0f, q.y );
    ASSERT_EQ( 0.0f, q.z );
}

TEST( Quaternion, fromMat4 )
{
    mat4 m = mat4::IDENTITY;
    quat q = fromMat4( m );

    ASSERT_EQ( 1.0f, q.w );
    ASSERT_EQ( 0.0f, q.x );
    ASSERT_EQ( 0.0f, q.y );
    ASSERT_EQ( 0.0f, q.z );
}

TEST( Quaternion, ToMat3 )
{
    quat q;
    mat3 m = toMat3( q );

    ASSERT_EQ( mat3::IDENTITY, m );
}

TEST( Quaternion, ToMat4 )
{
    quat q;
    // Explicit conversion
    mat4 m = toMat4( q );

    ASSERT_EQ( mat4::IDENTITY, m );
}

TEST( Quaternion, Transform_Vector3 )
{
    vec3 v = vec3::UNIT_X;
    quat q;

    auto w = q * v;

    ASSERT_EQ( v, w );
}

TEST( Quaternion, Vector3_Transform )
{
    vec3 v = vec3::UNIT_X;
    quat q;

    auto w = v * q;

    ASSERT_EQ( v, w );
}

TEST( Quaternion, Transform_Vector4 )
{
    vec4 v = vec4::UNIT_X;
    quat q;

    auto w = q * v;

    ASSERT_EQ( v, w );
}

TEST( Quaternion, Vector4_Transform )
{
    vec4 v = vec4::UNIT_X;
    quat q;

    auto w = v * q;

    ASSERT_EQ( v, w );
}

TEST( Quaternion, Lerp )
{
    quat a = axisAngle( vec3::UNIT_X, 0.0f );
    quat b = axisAngle( vec3::UNIT_X, PI<float> );

    quat c = lerp( a, b, 0.0f );
    quat d = lerp( a, b, 1.0f );

    ASSERT_EQ( a, c );
    ASSERT_EQ( b, d );
}

TEST( Quaternion, Slerp )
{
    quat a = axisAngle( vec3::UNIT_X, 0.0f );
    quat b = axisAngle( vec3::UNIT_X, PI_OVER_TWO<float> );

    quat c = slerp( a, b, 0.0f );
    quat d = slerp( a, b, 1.0f );

    ASSERT_TRUE( all( equal( a, c, EPSILON<float> ) ) );
    ASSERT_TRUE( all( equal( b, d, EPSILON<float> ) ) );
}

TEST( Quaternion, UnaryMinus )
{
    quat q { 1, 2, 3, 4 };
    quat n = -q;

    ASSERT_EQ( -1.0f, n.w );
    ASSERT_EQ( -2.0f, n.x );
    ASSERT_EQ( -3.0f, n.y );
    ASSERT_EQ( -4.0f, n.z );
}

TEST( Quaternion, Slerp_ShortestPath )
{
    // q and -q represent the same rotation, so slerp should not rotate at all.
    quat a = axisAngle( vec3::UNIT_Y, 0.5f );
    quat b = -a;

    quat c = slerp( a, b, 0.5f );

    ASSERT_TRUE( isNormalized( c ) );
    ASSERT_TRUE( all( equal( a, c, 1e-6f ) ) );
}

TEST( Quaternion, Slerp_NegativeDot )
{
    // b is a rotation of 90 degrees, but on the "far" side of the hypersphere.
    quat a = axisAngle( vec3::UNIT_X, 0.0f );
    quat b = -axisAngle( vec3::UNIT_X, PI_OVER_TWO<float> );

    quat c = slerp( a, b, 0.5f );
    quat e = axisAngle( vec3::UNIT_X, PI_OVER_TWO<float> * 0.5f );

    ASSERT_TRUE( all( equal( e, c, 1e-6f ) ) );
}

TEST( Quaternion, Pow0 )
{
    quat a = axisAngle( vec3::UNIT_X, PI<float> );
    quat b = pow( a, 0.0f );

    ASSERT_EQ( quat::IDENTITY, b );
}

TEST( Quaternion, Pow1 )
{
    quat a = axisAngle( vec3::UNIT_X, PI<float> );
    quat b = pow( a, 1.0f );

//    ASSERT_EQ( a, b ); // This fails in release builds with aggressive optimizations.
    ASSERT_FLOAT_EQ( a.x, b.x );
    ASSERT_FLOAT_EQ( a.y, b.y );
    ASSERT_FLOAT_EQ( a.z, b.z );
    //ASSERT_FLOAT_EQ( a.w, b.w );
    ASSERT_TRUE( abs(a.w - b.w) < EPSILON<float> );
}

TEST( Quaternion, LessThan )
{
    quat a { 1, 0, 0, 0 };
    quat b { 2, 0, 0, 0 };

    auto res = lessThan( a, b );

    ASSERT_TRUE( any( res ) );
}

TEST( Quaternion, LessThanEqual )
{
    quat a { 1, 0, 0, 0 };
    quat b { 2, 0, 0, 0 };

    auto res = lessThanEqual( a, b );

    ASSERT_TRUE( all( res ) );
}

TEST( Quaternion, Constexpr )
{
    static_assert( quat::IDENTITY[0] == 1.0f && quat::IDENTITY[1] == 0.0f );
    static_assert( quat::IDENTITY == quat {} );
}

TEST( Quaternion, Scalar_Multiplication_Commutes )
{
    quat q { 1, 2, 3, 4 };

    ASSERT_EQ( 2.0f * q, q * 2.0f );
    ASSERT_EQ( 2.0f * q, ( quat { 2, 4, 6, 8 } ) );
}

TEST( Quaternion, Constexpr_Arithmetic )
{
    constexpr quat a { 1, 2, 3, 4 };
    constexpr quat b { 5, 6, 7, 8 };

    static_assert( a + b == quat { 6, 8, 10, 12 } );
    static_assert( b - a == quat { 4, 4, 4, 4 } );
    static_assert( a * b == quat { -60, 12, 30, 24 } );
    static_assert( dot( a, b ) == 70.0f );
    static_assert( conjugate( a ) == quat { 1, -2, -3, -4 } );
    static_assert( inverse( quat::IDENTITY ) == quat::IDENTITY );

    // 180 degree rotation about the z-axis.
    constexpr quat r { 0, 0, 0, 1 };
    static_assert( r * vec3::UNIT_X == -vec3::UNIT_X );
    static_assert( r * vec4 { 1, 0, 0, 1 } == vec4 { -1, 0, 0, 1 } );
}

TEST( Quaternion, Pitch_Combined )
{
    // Pitch must also be correct when the rotation has yaw and roll components.
    const vec3 eulerAngles { 0.3f, 0.2f, 0.1f };
    const quat q { eulerAngles };

    ASSERT_NEAR( eulerAngles.x, FastMath::pitch( q ), 1e-5f );
}

TEST( Quaternion, SameRotation )
{
    const quat q = axisAngle( vec3::UNIT_Y, radians( 30.0f ) );

    // q and -q are different quaternions, but the same rotation.
    ASSERT_NE( q, -q );
    ASSERT_TRUE( sameRotation( q, -q ) );
    ASSERT_EQ( q * vec3::UNIT_X, -q * vec3::UNIT_X );

    ASSERT_TRUE( sameRotation( q, q ) );
    ASSERT_FALSE( sameRotation( q, axisAngle( vec3::UNIT_Y, radians( 31.0f ) ) ) );
    ASSERT_FALSE( sameRotation( q, conjugate( q ) ) );
}
