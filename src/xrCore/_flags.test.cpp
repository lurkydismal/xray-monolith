#include "stdafx.h"

#include "_flags.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

namespace
{
    enum class TestFlags : std::uint8_t
    {
        None  = 0,
        Read  = 1,
        Write = 2,
        Exec  = 3,
        Admin = 4,
    };

    enum class SparseFlags : std::uint8_t
    {
        First  = 0,
        Second = 1,
        Third  = 2,
        Fourth = 3,
    };
}


// =============================================================================
// _flags<T>
// =============================================================================

// -----------------------------------------------------------------------------
// get / zero / one
// -----------------------------------------------------------------------------

TEST(Flags, GetReturnsCurrentValue)
{
    Flags32 flags;
    flags.flags = 0x12345678u;

    EXPECT_EQ(flags.get(), 0x12345678u);
}


TEST(Flags, ZeroClearsAllBits)
{
    Flags32 flags;
    flags.flags = 0xffffffffu;

    EXPECT_EQ(&flags.zero(), &flags);
    EXPECT_EQ(flags.get(), 0u);
}


TEST(Flags, ZeroWorksWhenAlreadyZero)
{
    Flags32 flags;
    flags.flags = 0;

    flags.zero();

    EXPECT_EQ(flags.get(), 0u);
}


TEST(Flags, OneSetsAllBits)
{
    Flags32 flags;
    flags.flags = 0;

    EXPECT_EQ(&flags.one(), &flags);
    EXPECT_EQ(flags.get(), 0xffffffffu);
}


TEST(Flags, OneSetsAllBitsForDifferentIntegerWidths)
{
    Flags8 flags8;
    Flags16 flags16;
    Flags32 flags32;
    Flags64 flags64;

    flags8.one();
    flags16.one();
    flags32.one();
    flags64.one();

    EXPECT_EQ(flags8.get(), static_cast<u8>(0xff));
    EXPECT_EQ(flags16.get(), static_cast<u16>(0xffff));
    EXPECT_EQ(flags32.get(), static_cast<u32>(0xffffffffu));
    EXPECT_EQ(flags64.get(), static_cast<u64>(0xffffffffffffffffull));
}


// -----------------------------------------------------------------------------
// invert
// -----------------------------------------------------------------------------

TEST(Flags, InvertFlipsAllBits)
{
    Flags8 flags;
    flags.flags = 0x0fu;

    EXPECT_EQ(&flags.invert(), &flags);
    EXPECT_EQ(flags.get(), 0xf0u);
}


TEST(Flags, InvertFlipsAllBitsForZero)
{
    Flags16 flags;
    flags.zero();

    flags.invert();

    EXPECT_EQ(flags.get(), 0xffffu);
}


TEST(Flags, InvertFromOtherFlags)
{
    Flags8 source;
    source.flags = 0x0fu;

    Flags8 destination;
    destination.flags = 0x55u;

    EXPECT_EQ(&destination.invert(source), &destination);
    EXPECT_EQ(destination.get(), static_cast<u8>(~u8(0x0f)));
}


TEST(Flags, InvertMaskTogglesSelectedBits)
{
    Flags8 flags;
    flags.flags = 0b00001111;

    EXPECT_EQ(
        &flags.invert(static_cast<u8>(0b00110011)),
        &flags
    );

    EXPECT_EQ(flags.get(), 0b00111100u);
}


TEST(Flags, InvertMaskCanToggleBitsBack)
{
    Flags8 flags;
    flags.flags = 0b00001111;

    flags.invert(static_cast<u8>(0b00110011));
    flags.invert(static_cast<u8>(0b00110011));

    EXPECT_EQ(flags.get(), 0b00001111u);
}


// -----------------------------------------------------------------------------
// assign
// -----------------------------------------------------------------------------

TEST(Flags, AssignFromOtherFlags)
{
    Flags32 source;
    source.flags = 0x12345678u;

    Flags32 destination;
    destination.flags = 0xffffffffu;

    EXPECT_EQ(&destination.assign(source), &destination);
    EXPECT_EQ(destination.get(), source.get());
}


TEST(Flags, AssignFromMask)
{
    Flags32 flags;
    flags.flags = 0xffffffffu;

    EXPECT_EQ(
        &flags.assign(0x12345678u),
        &flags
    );

    EXPECT_EQ(flags.get(), 0x12345678u);
}


// -----------------------------------------------------------------------------
// set
// -----------------------------------------------------------------------------

TEST(Flags, SetEnablesSelectedBits)
{
    Flags8 flags;
    flags.flags = 0;

    EXPECT_EQ(
        &flags.set(static_cast<u8>(0x05), TRUE),
        &flags
    );

    EXPECT_EQ(flags.get(), 0x05u);
}


TEST(Flags, SetDisablesSelectedBits)
{
    Flags8 flags;
    flags.flags = 0xff;

    EXPECT_EQ(
        &flags.set(static_cast<u8>(0x05), FALSE),
        &flags
    );

    EXPECT_EQ(flags.get(), 0xfau);
}


TEST(Flags, SetTrueDoesNotClearOtherBits)
{
    Flags8 flags;
    flags.flags = 0b10100000;

    flags.set(static_cast<u8>(0b00000101), TRUE);

    EXPECT_EQ(flags.get(), 0b10100101u);
}


TEST(Flags, SetFalseDoesNotClearUnselectedBits)
{
    Flags8 flags;
    flags.flags = 0b10100101;

    flags.set(static_cast<u8>(0b00000101), FALSE);

    EXPECT_EQ(flags.get(), 0b10100000u);
}


// -----------------------------------------------------------------------------
// is / is_any / test
// -----------------------------------------------------------------------------

TEST(Flags, IsReturnsTrueWhenAllMaskBitsAreSet)
{
    Flags8 flags;
    flags.flags = 0b11110000;

    EXPECT_TRUE(flags.is(static_cast<u8>(0b11000000)));
}


TEST(Flags, IsReturnsFalseWhenAnyMaskBitIsMissing)
{
    Flags8 flags;
    flags.flags = 0b10100000;

    EXPECT_FALSE(flags.is(static_cast<u8>(0b11000000)));
}


TEST(Flags, IsReturnsTrueForZeroMask)
{
    Flags8 flags;
    flags.flags = 0;

    EXPECT_TRUE(flags.is(static_cast<u8>(0)));
}


TEST(Flags, IsAnyReturnsTrueWhenAtLeastOneBitIsSet)
{
    Flags8 flags;
    flags.flags = 0b00000100;

    EXPECT_TRUE(flags.is_any(static_cast<u8>(0b00000110)));
}


TEST(Flags, IsAnyReturnsFalseWhenNoMaskBitsAreSet)
{
    Flags8 flags;
    flags.flags = 0b00000100;

    EXPECT_FALSE(flags.is_any(static_cast<u8>(0b00000011)));
}


TEST(Flags, TestMatchesIsAny)
{
    Flags8 flags;
    flags.flags = 0b01010000;

    const u8 mask = 0b01100000;

    EXPECT_EQ(flags.test(mask), flags.is_any(mask));
}


TEST(Flags, TestReturnsFalseForZeroMask)
{
    Flags8 flags;
    flags.flags = 0xff;

    EXPECT_FALSE(flags.test(static_cast<u8>(0)));
}


// -----------------------------------------------------------------------------
// assign_or
// -----------------------------------------------------------------------------

TEST(Flags, AssignOrAddsBits)
{
    Flags8 flags;
    flags.flags = 0b00001100;

    EXPECT_EQ(
        &flags.assign_or(static_cast<u8>(0b00110000)),
        &flags
    );

    EXPECT_EQ(flags.get(), 0b00111100u);
}


TEST(Flags, AssignOrDoesNotClearExistingBits)
{
    Flags8 flags;
    flags.flags = 0xff;

    flags.assign_or(static_cast<u8>(0));

    EXPECT_EQ(flags.get(), 0xffu);
}


TEST(Flags, AssignOrFromOtherFlagsAndMask)
{
    Flags8 source;
    source.flags = 0b10101010;

    Flags8 destination;
    destination.flags = 0xffffffffu;

    EXPECT_EQ(
        &destination.assign_or(
            source,
            static_cast<u8>(0b00000101)
        ),
        &destination
    );

    EXPECT_EQ(destination.get(), 0b10101111u);
}


// -----------------------------------------------------------------------------
// assign_and
// -----------------------------------------------------------------------------

TEST(Flags, AssignAndKeepsOnlyMaskBits)
{
    Flags8 flags;
    flags.flags = 0b11110000;

    EXPECT_EQ(
        &flags.assign_and(static_cast<u8>(0b11001100)),
        &flags
    );

    EXPECT_EQ(flags.get(), 0b11000000u);
}


TEST(Flags, AssignAndWithZeroClearsEverything)
{
    Flags8 flags;
    flags.flags = 0xff;

    flags.assign_and(static_cast<u8>(0));

    EXPECT_EQ(flags.get(), 0u);
}


TEST(Flags, AssignAndFromOtherFlagsAndMask)
{
    Flags8 source;
    source.flags = 0b10101111;

    Flags8 destination;
    destination.flags = 0xff;

    EXPECT_EQ(
        &destination.assign_and(
            source,
            static_cast<u8>(0b00001111)
        ),
        &destination
    );

    EXPECT_EQ(destination.get(), 0b00001111u);
}


// -----------------------------------------------------------------------------
// equal
// -----------------------------------------------------------------------------

TEST(Flags, EqualReturnsTrueForIdenticalValues)
{
    Flags32 a;
    Flags32 b;

    a.flags = 0x12345678u;
    b.flags = 0x12345678u;

    EXPECT_TRUE(a.equal(b));
}


TEST(Flags, EqualReturnsFalseForDifferentValues)
{
    Flags32 a;
    Flags32 b;

    a.flags = 0x12345678u;
    b.flags = 0x12345679u;

    EXPECT_FALSE(a.equal(b));
}


TEST(Flags, EqualWithMaskIgnoresUnmaskedBits)
{
    Flags8 a;
    Flags8 b;

    a.flags = 0b10101111;
    b.flags = 0b01001111;

    EXPECT_TRUE(
        a.equal(
            b,
            static_cast<u8>(0x0f)
        )
    );
}


TEST(Flags, EqualWithMaskDetectsDifferenceInMaskedBits)
{
    Flags8 a;
    Flags8 b;

    a.flags = 0b10101111;
    b.flags = 0b01000111;

    EXPECT_FALSE(
        a.equal(
            b,
            static_cast<u8>(0x0f)
        )
    );
}


TEST(Flags, EqualWithZeroMaskAlwaysReturnsTrue)
{
    Flags8 a;
    Flags8 b;

    a.flags = 0xff;
    b.flags = 0;

    EXPECT_TRUE(
        a.equal(
            b,
            static_cast<u8>(0)
        )
    );
}


// -----------------------------------------------------------------------------
// Chaining
// -----------------------------------------------------------------------------

TEST(Flags, OperationsCanBeChained)
{
    Flags8 flags;

    flags.zero()
         .assign_or(static_cast<u8>(0x01))
         .assign_or(static_cast<u8>(0x04))
         .set(static_cast<u8>(0x01), FALSE)
         .set(static_cast<u8>(0x02), TRUE);

    EXPECT_EQ(flags.get(), 0x06u);
}


// =============================================================================
// xr_bitsetflags<EnumT>
// =============================================================================

// -----------------------------------------------------------------------------
// Initial state
// -----------------------------------------------------------------------------

TEST(BitsetFlags, StartsEmpty)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_TRUE(flags.none());
    EXPECT_FALSE(flags.any());
    EXPECT_EQ(flags.count(), 0u);
}


TEST(BitsetFlags, SizeMatchesEnumCount)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_EQ(flags.size(), 4u);
}


// -----------------------------------------------------------------------------
// set / reset
// -----------------------------------------------------------------------------

TEST(BitsetFlags, SetEnablesEnumFlag)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_EQ(
        &flags.set(TestFlags::Read),
        &flags
    );

    EXPECT_TRUE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags[TestFlags::Read]);
    EXPECT_EQ(flags.count(), 1u);
}


TEST(BitsetFlags, SetCanExplicitlyDisableEnumFlag)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Read, false);

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags.none());
}


TEST(BitsetFlags, ResetDisablesEnumFlag)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Write);

    EXPECT_EQ(
        &flags.reset(TestFlags::Read),
        &flags
    );

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags.test(TestFlags::Write));
    EXPECT_EQ(flags.count(), 1u);
}


TEST(BitsetFlags, ResetWithoutArgumentClearsAllFlags)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Write);
    flags.set(TestFlags::Exec);

    EXPECT_EQ(
        &flags.reset(),
        &flags
    );

    EXPECT_TRUE(flags.none());
    EXPECT_EQ(flags.count(), 0u);
}


// -----------------------------------------------------------------------------
// any / none / all
// -----------------------------------------------------------------------------

TEST(BitsetFlags, AnyReturnsFalseWhenEmpty)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_FALSE(flags.any());
}


TEST(BitsetFlags, AnyReturnsTrueWhenFlagIsSet)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Admin);

    EXPECT_TRUE(flags.any());
}


TEST(BitsetFlags, NoneReturnsTrueWhenEmpty)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_TRUE(flags.none());
}


TEST(BitsetFlags, NoneReturnsFalseWhenFlagIsSet)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);

    EXPECT_FALSE(flags.none());
}


TEST(BitsetFlags, AllReturnsTrueWhenEveryBitIsSet)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set();

    EXPECT_TRUE(flags.all());
    EXPECT_EQ(flags.count(), flags.size());
}


TEST(BitsetFlags, AllReturnsFalseWhenNotEveryBitIsSet)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);

    EXPECT_FALSE(flags.all());
}


// -----------------------------------------------------------------------------
// count
// -----------------------------------------------------------------------------

TEST(BitsetFlags, CountTracksNumberOfSetFlags)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_EQ(flags.count(), 0u);

    flags.set(TestFlags::Read);
    EXPECT_EQ(flags.count(), 1u);

    flags.set(TestFlags::Write);
    EXPECT_EQ(flags.count(), 2u);

    flags.set(TestFlags::Exec);
    EXPECT_EQ(flags.count(), 3u);

    flags.reset(TestFlags::Write);
    EXPECT_EQ(flags.count(), 2u);
}


// -----------------------------------------------------------------------------
// zero / one
// -----------------------------------------------------------------------------

TEST(BitsetFlags, ZeroClearsAllBits)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set();

    EXPECT_EQ(&flags.zero(), &flags);

    EXPECT_TRUE(flags.none());
    EXPECT_EQ(flags.count(), 0u);
}


TEST(BitsetFlags, OneSetsAllBits)
{
    xr_bitsetflags<TestFlags> flags;

    EXPECT_EQ(&flags.one(), &flags);

    EXPECT_TRUE(flags.all());
    EXPECT_EQ(flags.count(), flags.size());
}


// -----------------------------------------------------------------------------
// flip / invert
// -----------------------------------------------------------------------------

TEST(BitsetFlags, FlipInvertsAllBits)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Exec);

    flags.flip();

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags.test(TestFlags::Write));
    EXPECT_FALSE(flags.test(TestFlags::Exec));
    EXPECT_TRUE(flags.test(TestFlags::Admin));
}


TEST(BitsetFlags, InvertIsAliasForFlip)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Admin);

    flags.invert();

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags.test(TestFlags::Write));
    EXPECT_TRUE(flags.test(TestFlags::Exec));
    EXPECT_FALSE(flags.test(TestFlags::Admin));
}


TEST(BitsetFlags, FlipTwiceRestoresOriginalState)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Exec);

    flags.flip();
    flags.flip();

    EXPECT_TRUE(flags.test(TestFlags::Read));
    EXPECT_FALSE(flags.test(TestFlags::Write));
    EXPECT_TRUE(flags.test(TestFlags::Exec));
    EXPECT_FALSE(flags.test(TestFlags::Admin));
}


// -----------------------------------------------------------------------------
// test by enum and by position
// -----------------------------------------------------------------------------

TEST(BitsetFlags, TestByEnumMatchesOperatorSubscript)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Write);

    EXPECT_TRUE(flags.test(TestFlags::Write));
    EXPECT_TRUE(flags[TestFlags::Write]);

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_FALSE(flags[TestFlags::Read]);
}


TEST(BitsetFlags, TestByPosition)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Exec);

    EXPECT_TRUE(flags.test(0u));
    EXPECT_FALSE(flags.test(1u));
    EXPECT_TRUE(flags.test(2u));
    EXPECT_FALSE(flags.test(3u));
}


// -----------------------------------------------------------------------------
// getBitsetAsMap
// -----------------------------------------------------------------------------

TEST(BitsetFlags, GetBitsetAsMapContainsEveryEnumName)
{
    xr_bitsetflags<TestFlags> flags;

    const auto result = flags.getBitsetAsMap();

    ASSERT_EQ(result.size(), 4u);

    EXPECT_TRUE(result.contains("Read"));
    EXPECT_TRUE(result.contains("Write"));
    EXPECT_TRUE(result.contains("Exec"));
    EXPECT_TRUE(result.contains("Admin"));
}


TEST(BitsetFlags, GetBitsetAsMapReflectsFlagState)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);
    flags.set(TestFlags::Exec);

    const auto result = flags.getBitsetAsMap();

    ASSERT_EQ(result.size(), 4u);

    EXPECT_TRUE(result.at("Read"));
    EXPECT_FALSE(result.at("Write"));
    EXPECT_TRUE(result.at("Exec"));
    EXPECT_FALSE(result.at("Admin"));
}


TEST(BitsetFlags, GetBitsetAsMapIsEmptyForNoSetFlags)
{
    xr_bitsetflags<TestFlags> flags;

    const auto result = flags.getBitsetAsMap();

    EXPECT_FALSE(result.at("Read"));
    EXPECT_FALSE(result.at("Write"));
    EXPECT_FALSE(result.at("Exec"));
    EXPECT_FALSE(result.at("Admin"));
}


TEST(BitsetFlags, GetBitsetAsMapShowsAllFlagsAfterOne)
{
    xr_bitsetflags<TestFlags> flags;

    flags.one();

    const auto result = flags.getBitsetAsMap();

    EXPECT_TRUE(result.at("Read"));
    EXPECT_TRUE(result.at("Write"));
    EXPECT_TRUE(result.at("Exec"));
    EXPECT_TRUE(result.at("Admin"));
}


// -----------------------------------------------------------------------------
// Chaining
// -----------------------------------------------------------------------------

TEST(BitsetFlags, OperationsCanBeChained)
{
    xr_bitsetflags<TestFlags> flags;

    flags.zero()
         .set(TestFlags::Read)
         .set(TestFlags::Write)
         .reset(TestFlags::Read);

    EXPECT_FALSE(flags.test(TestFlags::Read));
    EXPECT_TRUE(flags.test(TestFlags::Write));
}


// -----------------------------------------------------------------------------
// Boundary / underlying representation
// -----------------------------------------------------------------------------

TEST(BitsetFlags, FirstEnumValueMapsToFirstBit)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Read);

    EXPECT_TRUE(flags.test(0u));
    EXPECT_FALSE(flags.test(1u));
}


TEST(BitsetFlags, LastEnumValueMapsToLastBit)
{
    xr_bitsetflags<TestFlags> flags;

    flags.set(TestFlags::Admin);

    EXPECT_FALSE(flags.test(0u));
    EXPECT_FALSE(flags.test(1u));
    EXPECT_FALSE(flags.test(2u));
    EXPECT_TRUE(flags.test(3u));
}
