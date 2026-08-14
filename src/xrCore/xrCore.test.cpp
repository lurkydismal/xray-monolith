#include "xrCore.h"

#include <gtest/gtest.h>

#include "stdafx.h"

namespace {

// -----------------------------------------------------------------------------
// xr_rtoken
// -----------------------------------------------------------------------------

TEST( XrCoreRToken, Constructor ) {
    xr_rtoken token( "test", 42 );

    EXPECT_EQ( token.id, 42 );
    EXPECT_STREQ( *token.name, "test" );
}

TEST( XrCoreRToken, Rename ) {
    xr_rtoken token( "old", 1 );

    token.rename( "new" );

    EXPECT_STREQ( *token.name, "new" );
    EXPECT_EQ( token.id, 1 );
}

TEST( XrCoreRToken, RenameToEmpty ) {
    xr_rtoken token( "old", 1 );

    token.rename( "" );

    EXPECT_STREQ( *token.name, "" );
    EXPECT_EQ( token.id, 1 );
}

#if 0
TEST(XrCoreRToken, Equal)
{
    xr_rtoken token("test", 42);

    EXPECT_TRUE(token.equal("test"));
    EXPECT_FALSE(token.equal("other"));
}

TEST(XrCoreRToken, EqualIsCaseSensitive)
{
    xr_rtoken token("Test", 42);

    EXPECT_TRUE(token.equal("Test"));
    EXPECT_FALSE(token.equal("test"));
}

TEST(XrCoreRToken, EqualEmpty)
{
    xr_rtoken token("", 42);

    EXPECT_TRUE(token.equal(""));
    EXPECT_FALSE(token.equal("test"));
}
#endif

// -----------------------------------------------------------------------------
// xr_shortcut
// -----------------------------------------------------------------------------

TEST( XrCoreShortcut, DefaultConstructor ) {
    xr_shortcut shortcut;

    EXPECT_EQ( shortcut.key, 0 );
    EXPECT_EQ( shortcut.hotkey, 0 );
}

TEST( XrCoreShortcut, KeyOnly ) {
    constexpr u8 key = 0x41;

    xr_shortcut shortcut( key, FALSE, FALSE, FALSE );

    EXPECT_EQ( shortcut.key, key );
    EXPECT_EQ( shortcut.hotkey, key );
}

TEST( XrCoreShortcut, Alt ) {
    xr_shortcut shortcut( 0x41, TRUE, FALSE, FALSE );

    EXPECT_EQ( shortcut.key, 0x41 );
    EXPECT_EQ( shortcut.hotkey,
               u16( 0x41 ) | ( u16( xr_shortcut::flAlt ) << 8 ) );
}

TEST( XrCoreShortcut, Ctrl ) {
    xr_shortcut shortcut( 0x41, FALSE, TRUE, FALSE );

    EXPECT_EQ( shortcut.key, 0x41 );
    EXPECT_EQ( shortcut.hotkey,
               u16( 0x41 ) | ( u16( xr_shortcut::flCtrl ) << 8 ) );
}

TEST( XrCoreShortcut, Shift ) {
    xr_shortcut shortcut( 0x41, FALSE, FALSE, TRUE );

    EXPECT_EQ( shortcut.key, 0x41 );
    EXPECT_EQ( shortcut.hotkey,
               u16( 0x41 ) | ( u16( xr_shortcut::flShift ) << 8 ) );
}

TEST( XrCoreShortcut, AllModifiers ) {
    xr_shortcut shortcut( 0x41, TRUE, TRUE, TRUE );

    constexpr u8 modifiers =
        xr_shortcut::flAlt | xr_shortcut::flCtrl | xr_shortcut::flShift;

    EXPECT_EQ( shortcut.key, 0x41 );
    EXPECT_EQ( shortcut.hotkey, u16( 0x41 ) | ( u16( modifiers ) << 8 ) );
}

#if 0
TEST(XrCoreShortcut, ModifierFlagsAreIndependent)
{
    xr_shortcut alt(0x41, TRUE, FALSE, FALSE);
    xr_shortcut ctrl(0x41, FALSE, TRUE, FALSE);
    xr_shortcut shift(0x41, FALSE, FALSE, TRUE);

    EXPECT_TRUE(alt.ext.equal(xr_shortcut::flAlt));
    EXPECT_TRUE(ctrl.ext.equal(xr_shortcut::flCtrl));
    EXPECT_TRUE(shift.ext.equal(xr_shortcut::flShift));
}
#endif

TEST( XrCoreShortcut, SimilarSameKeyAndModifiers ) {
    xr_shortcut a( 0x41, TRUE, TRUE, FALSE );
    xr_shortcut b( 0x41, TRUE, TRUE, FALSE );

    EXPECT_TRUE( a.similar( b ) );
}

TEST( XrCoreShortcut, SimilarRequiresSameKey ) {
    xr_shortcut a( 0x41, TRUE, TRUE, FALSE );
    xr_shortcut b( 0x42, TRUE, TRUE, FALSE );

    EXPECT_FALSE( a.similar( b ) );
}

TEST( XrCoreShortcut, SimilarRequiresSameModifiers ) {
    xr_shortcut a( 0x41, TRUE, TRUE, FALSE );
    xr_shortcut b( 0x41, TRUE, FALSE, FALSE );

    EXPECT_FALSE( a.similar( b ) );
}

TEST( XrCoreShortcut, SimilarIsSymmetric ) {
    xr_shortcut a( 0x41, TRUE, FALSE, TRUE );
    xr_shortcut b( 0x41, TRUE, FALSE, TRUE );

    EXPECT_EQ( a.similar( b ), b.similar( a ) );
}

TEST( XrCoreShortcut, HotkeyContainsKeyAndModifiers ) {
    xr_shortcut shortcut( 0x41, TRUE, TRUE, TRUE );

    const u16 expected =
        u16( 0x41 ) |
        ( u16( xr_shortcut::flAlt | xr_shortcut::flCtrl | xr_shortcut::flShift )
          << 8 );

    EXPECT_EQ( shortcut.hotkey, expected );
}

TEST( XrCoreShortcut, IsPackedToTwoBytes ) {
    EXPECT_EQ( sizeof( xr_shortcut ), sizeof( u16 ) );
}

// -----------------------------------------------------------------------------
// xrCore::isDebug
// -----------------------------------------------------------------------------

TEST( XrCore, IsDebugFalseByDefault ) {
    xrCore core;

    EXPECT_FALSE( core.isDebug() );
}

TEST( XrCore, IsDebugWhenDbgSet ) {
    xrCore core;
    core.ParamsData.set( ECoreParams::dbg );

    EXPECT_TRUE( core.isDebug() );
}

TEST( XrCore, IsDebugWhenDbgDevSet ) {
    xrCore core;
    core.ParamsData.set( ECoreParams::dbgdev );

    EXPECT_TRUE( core.isDebug() );
}

TEST( XrCore, IsDebugWhenDbgActSet ) {
    xrCore core;
    core.ParamsData.set( ECoreParams::dbgact );

    EXPECT_TRUE( core.isDebug() );
}

TEST( XrCore, IsDebugWhenDbgBulletSet ) {
    xrCore core;
    core.ParamsData.set( ECoreParams::dbgbullet );

    EXPECT_TRUE( core.isDebug() );
}

TEST( XrCore, IsDebugIgnoresUnrelatedFlags ) {
    xrCore core;

    // ECoreParams is project-specific. These are deliberately tested through
    // the flags that isDebug() actually examines.
    EXPECT_FALSE( core.isDebug() );

    core.ParamsData.set( ECoreParams::build );

    EXPECT_FALSE( core.isDebug() );
}

TEST( XrCore, IsDebugRemainsTrueWithMultipleDebugFlags ) {
    xrCore core;

    core.ParamsData.set( ECoreParams::dbg );
    core.ParamsData.set( ECoreParams::dbgdev );
    core.ParamsData.set( ECoreParams::dbgact );
    core.ParamsData.set( ECoreParams::dbgbullet );

    EXPECT_TRUE( core.isDebug() );
}

// -----------------------------------------------------------------------------
// destructor<T>
// -----------------------------------------------------------------------------

namespace {
struct DestructorTestObject {
    static int destructor_count;

    ~DestructorTestObject() { ++destructor_count; }
};

int DestructorTestObject::destructor_count = 0;
} // namespace

TEST( XrCoreDestructor, DeletesObject ) {
    DestructorTestObject::destructor_count = 0;

    {
        destructor< DestructorTestObject > d( new DestructorTestObject );

        EXPECT_EQ( DestructorTestObject::destructor_count, 0 );
    }

    EXPECT_EQ( DestructorTestObject::destructor_count, 1 );
}

TEST( XrCoreDestructor, OperatorReturnsReferencedObject ) {
    auto* object = new DestructorTestObject;

    destructor< DestructorTestObject > d( object );

    EXPECT_EQ( &d(), object );
}

TEST( XrCoreDestructor, OperatorAllowsObjectMutation ) {
    struct TestObject {
        int value = 0;
    };

    auto* object = new TestObject;

    destructor< TestObject > d( object );

    d().value = 42;

    EXPECT_EQ( d().value, 42 );
}

TEST( XrCoreDestructor, DeletesExactlyOnce ) {
    DestructorTestObject::destructor_count = 0;

    {
        destructor< DestructorTestObject > d( new DestructorTestObject );
        EXPECT_EQ( DestructorTestObject::destructor_count, 0 );
    }

    EXPECT_EQ( DestructorTestObject::destructor_count, 1 );
}

// -----------------------------------------------------------------------------
// CRC32
// -----------------------------------------------------------------------------

TEST( XrCoreCrc32, EmptyInput ) {
    EXPECT_EQ( crc32( "", 0 ), 0u );
}

TEST( XrCoreCrc32, KnownValue ) {
    // CRC32 implementation used by X-Ray.
    //
    // Keep this as a fixed regression value rather than calculating the
    // expected value using another CRC implementation in the test.
    constexpr char input[] = "123456789";

    EXPECT_EQ( crc32( input, sizeof( input ) - 1 ), 0xCBF43926u );
}

TEST( XrCoreCrc32, SameInputProducesSameResult ) {
    constexpr char input[] = "hello world";

    const u32 a = crc32( input, sizeof( input ) - 1 );
    const u32 b = crc32( input, sizeof( input ) - 1 );

    EXPECT_EQ( a, b );
}

TEST( XrCoreCrc32, DifferentInputProducesDifferentResult ) {
    constexpr char a[] = "hello";
    constexpr char b[] = "world";

    EXPECT_NE( crc32( a, sizeof( a ) - 1 ), crc32( b, sizeof( b ) - 1 ) );
}

TEST( XrCoreCrc32, LengthMatters ) {
    constexpr char input[] = "hello";

    EXPECT_NE( crc32( input, 3 ), crc32( input, sizeof( input ) - 1 ) );
}

TEST( XrCoreCrc32, StartingCrcAffectsResult ) {
    constexpr char input[] = "hello world";

    const u32 normal = crc32( input, sizeof( input ) - 1 );
    const u32 seeded = crc32( input, sizeof( input ) - 1, 0x12345678u );

    EXPECT_NE( normal, seeded );
}

TEST( XrCoreCrc32, IncrementalCrcMatchesSinglePass ) {
    constexpr char first[] = "hello ";
    constexpr char second[] = "world";

    const u32 single = crc32( "hello world", sizeof( "hello world" ) - 1 );

    const u32 incremental = crc32( second, sizeof( second ) - 1,
                                   crc32( first, sizeof( first ) - 1 ) );

    EXPECT_EQ( incremental, single );
}

// -----------------------------------------------------------------------------
// path_crc32
// -----------------------------------------------------------------------------

TEST( XrCorePathCrc32, SamePathProducesSameResult ) {
    constexpr char path[] = "textures/foo/bar.dds";

    EXPECT_EQ( path_crc32( path, sizeof( path ) - 1 ),
               path_crc32( path, sizeof( path ) - 1 ) );
}

TEST( XrCorePathCrc32, DifferentPathsProduceDifferentResults ) {
    constexpr char a[] = "textures/foo/bar.dds";
    constexpr char b[] = "textures/foo/baz.dds";

    EXPECT_NE( path_crc32( a, sizeof( a ) - 1 ),
               path_crc32( b, sizeof( b ) - 1 ) );
}

TEST( XrCorePathCrc32, LengthMatters ) {
    constexpr char path[] = "textures/foo/bar.dds";

    EXPECT_NE( path_crc32( path, 5 ), path_crc32( path, sizeof( path ) - 1 ) );
}

// -----------------------------------------------------------------------------
// Layout / ABI regression tests
// -----------------------------------------------------------------------------

TEST( XrCoreShortcut, KeyOffset ) {
    EXPECT_EQ( offsetof( xr_shortcut, key ), 0u );
}

TEST( XrCoreShortcut, ExtOffset ) {
    EXPECT_EQ( offsetof( xr_shortcut, ext ), 1u );
}

TEST( XrCoreShortcut, HotkeyOffset ) {
    EXPECT_EQ( offsetof( xr_shortcut, hotkey ), 0u );
}

TEST( XrCoreRToken, IdIsAfterName ) {
    // Do not assert sizeof(xr_rtoken): shared_str implementation may vary
    // during modernization. The important property here is that the fields
    // remain in declaration order.
    EXPECT_LT( offsetof( xr_rtoken, name ), offsetof( xr_rtoken, id ) );
}

} // namespace
