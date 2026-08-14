#ifdef DEBUG

#include "dump_string.h"

#include <gtest/gtest.h>

#include "stdafx.h"

namespace {
Fvector make_vector( float x, float y, float z ) {
    Fvector result;
    result.set( x, y, z );
    return result;
}

Fmatrix make_matrix() {
    Fmatrix result;

    result.i.set( 1.0f, 2.0f, 3.0f );
    result._14_ = 4.0f;

    result.j.set( 5.0f, 6.0f, 7.0f );
    result._24_ = 8.0f;

    result.k.set( 9.0f, 10.0f, 11.0f );
    result._34_ = 12.0f;

    result.c.set( 13.0f, 14.0f, 15.0f );
    result._44_ = 16.0f;

    return result;
}
} // namespace

// -----------------------------------------------------------------------------
// get_string(bool)
// -----------------------------------------------------------------------------

TEST( DumpString, GetStringBoolTrue ) {
    EXPECT_EQ( get_string( true ), "true" );
}

TEST( DumpString, GetStringBoolFalse ) {
    EXPECT_EQ( get_string( false ), "false" );
}

// -----------------------------------------------------------------------------
// get_string(Fvector)
// -----------------------------------------------------------------------------

TEST( DumpString, GetStringVector ) {
    const Fvector value = make_vector( 1.0f, 2.0f, 3.0f );

    EXPECT_EQ( get_string( value ), "( 1.000000, 2.000000, 3.000000 )" );
}

TEST( DumpString, GetStringVectorNegativeValues ) {
    const Fvector value = make_vector( -1.5f, -2.25f, -3.75f );

    EXPECT_EQ( get_string( value ), "( -1.500000, -2.250000, -3.750000 )" );
}

TEST( DumpString, GetStringVectorZero ) {
    const Fvector value = make_vector( 0.0f, 0.0f, 0.0f );

    EXPECT_EQ( get_string( value ), "( 0.000000, 0.000000, 0.000000 )" );
}

// -----------------------------------------------------------------------------
// get_string(Fmatrix)
// -----------------------------------------------------------------------------

TEST( DumpString, GetStringMatrix ) {
    const Fmatrix value = make_matrix();

    EXPECT_EQ( get_string( value ),
               "\n"
               "1.000000,2.000000,3.000000,4.000000\n"
               "5.000000,6.000000,7.000000,8.000000\n"
               "9.000000,10.000000,11.000000,12.000000\n"
               "13.000000,14.000000,15.000000,16.000000\n" );
}

TEST( DumpString, GetStringMatrixNegativeValues ) {
    Fmatrix value;

    value.i.set( -1.0f, -2.0f, -3.0f );
    value._14_ = -4.0f;

    value.j.set( -5.0f, -6.0f, -7.0f );
    value._24_ = -8.0f;

    value.k.set( -9.0f, -10.0f, -11.0f );
    value._34_ = -12.0f;

    value.c.set( -13.0f, -14.0f, -15.0f );
    value._44_ = -16.0f;

    EXPECT_EQ( get_string( value ),
               "\n"
               "-1.000000,-2.000000,-3.000000,-4.000000\n"
               "-5.000000,-6.000000,-7.000000,-8.000000\n"
               "-9.000000,-10.000000,-11.000000,-12.000000\n"
               "-13.000000,-14.000000,-15.000000,-16.000000\n" );
}

// -----------------------------------------------------------------------------
// get_string(Fbox)
// -----------------------------------------------------------------------------

TEST( DumpString, GetStringBox ) {
    Fbox value;
    value.min = make_vector( 1.0f, 2.0f, 3.0f );
    value.max = make_vector( 4.0f, 5.0f, 6.0f );

    EXPECT_EQ( get_string( value ),
               "[ min: ( 1.000000, 2.000000, 3.000000 ) - "
               "max: ( 4.000000, 5.000000, 6.000000 ) ]" );
}

TEST( DumpString, GetStringBoxNegativeValues ) {
    Fbox value;
    value.min = make_vector( -1.0f, -2.0f, -3.0f );
    value.max = make_vector( 4.0f, 5.0f, 6.0f );

    EXPECT_EQ( get_string( value ),
               "[ min: ( -1.000000, -2.000000, -3.000000 ) - "
               "max: ( 4.000000, 5.000000, 6.000000 ) ]" );
}

// -----------------------------------------------------------------------------
// dump_string(Fvector)
// -----------------------------------------------------------------------------

TEST( DumpString, DumpStringVector ) {
    const Fvector value = make_vector( 1.0f, 2.0f, 3.0f );

    EXPECT_EQ( dump_string( "position", value ),
               "position : (1.000000,2.000000,3.000000) " );
}

TEST( DumpString, DumpStringVectorEmptyName ) {
    const Fvector value = make_vector( 1.0f, 2.0f, 3.0f );

    EXPECT_EQ( dump_string( "", value ), " : (1.000000,2.000000,3.000000) " );
}

// -----------------------------------------------------------------------------
// dump_string(Fmatrix)
// -----------------------------------------------------------------------------

TEST( DumpString, DumpStringMatrix ) {
    const Fmatrix value = make_matrix();

    EXPECT_EQ(
        dump_string( "matrix", value ),
        "matrix.i,  : (1.000000,2.000000,3.000000) , _14_=4.000000 \n"
        "matrix.j,  : (5.000000,6.000000,7.000000) , _24_=8.000000 \n"
        "matrix.k,  : (9.000000,10.000000,11.000000) , _34_=12.000000 \n"
        "matrix.c,  : (13.000000,14.000000,15.000000) , _44_=16.000000 \n" );
}

TEST( DumpString, DumpStringMatrixNegativeValues ) {
    Fmatrix value;

    value.i.set( -1.0f, -2.0f, -3.0f );
    value._14_ = -4.0f;

    value.j.set( -5.0f, -6.0f, -7.0f );
    value._24_ = -8.0f;

    value.k.set( -9.0f, -10.0f, -11.0f );
    value._34_ = -12.0f;

    value.c.set( -13.0f, -14.0f, -15.0f );
    value._44_ = -16.0f;

    EXPECT_EQ(
        dump_string( "matrix", value ),
        "matrix.i,  : (-1.000000,-2.000000,-3.000000) , _14_=-4.000000 \n"
        "matrix.j,  : (-5.000000,-6.000000,-7.000000) , _24_=-8.000000 \n"
        "matrix.k,  : (-9.000000,-10.000000,-11.000000) , _34_=-12.000000 \n"
        "matrix.c,  : (-13.000000,-14.000000,-15.000000) , _44_=-16.000000 "
        "\n" );
}

#endif // DEBUG
