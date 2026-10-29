#include <FastMath/Transform.hpp>

#include <gtest/gtest.h>

using namespace FastMath;

TEST( Transform, DefaultConstruct )
{
    TransformF t;

    ASSERT_EQ( t.getMatrix(), mat4::IDENTITY );
}

TEST( Transform, Construct )
{
    TransformF t { vec3 { 2, 3, 4 }, vec3 { 5, 6, 7 } };

    mat4 expected = {
        2, 0, 0, 5,
        0, 3, 0, 6,
        0, 0, 4, 7,
        0, 0, 0, 1
    };

    ASSERT_EQ( t.getMatrix(), expected );
}

TEST( Transform, SetTranslate )
{
    TransformF t;
    t.setTranslate( { 1, 2, 3 } );

    ASSERT_EQ( t.getMatrix(), translate( vec3 { 1, 2, 3 } ) );
}

TEST( Transform, SetRotation )
{
    TransformF t;
    quat       q = axisAngle( vec3::UNIT_Y, 0.5f );
    t.setRotation( q );

    ASSERT_EQ( t.getMatrix(), toMat4( q ) );
}
