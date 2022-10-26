#include "gtest/gtest.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::CreateFlagSet;
using libEmbedded::bits::CreateMask;
using libEmbedded::bits::HasFlagSet;

TEST(BitMaskCreatorFixture, CreateMask10WithoutStartOffset)
{
    uint16_t mask = CreateMask(10);
    ASSERT_EQ(0b1111111111, mask);
}

TEST(BitMaskCreatorFixture, CreateMask5WithoutStartOffset)
{
    uint16_t mask = CreateMask(5);
    ASSERT_EQ(0b11111, mask);
}

TEST(BitMaskCreatorFixture, CreateMask10WithStartOf5)
{
    uint16_t mask = CreateMask(10, 5);
    ASSERT_EQ(0b111111111100000, mask);
}

TEST(BitMaskCreatorFixture, CreateMask5WithStartOf5)
{
    uint16_t mask = CreateMask(5, 5);
    ASSERT_EQ(0b1111100000, mask);
}

TEST(BitFlagCreatorFixture, SinglePositionArgInRangeOfType)
{
    uint8_t flags = CreateFlagSet<uint8_t, 5>();
    ASSERT_EQ((1 << 5), flags);
}

TEST(BitFlagCreatorFixture, SinglePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17>();
    ASSERT_EQ(0, flags);
}

TEST(BitFlagCreatorFixture, TwoPositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST(BitFlagCreatorFixture, TwoPositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 15>();
    ASSERT_EQ((1 << 15), flags);
}

TEST(BitFlagCreatorFixture, TwoPositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 15, 2>();
    ASSERT_EQ((1 << 15) | (1 << 2), flags);
}

TEST(BitFlagCreatorFixture, MultiplePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST(BitFlagCreatorFixture, MultiplePositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19, 8, 10, 16>();
    ASSERT_EQ((1 << 8) | (1 << 10), flags);
}

TEST(BitFlagCreatorFixture, MultiplePositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 15, 2, 8, 10>();
    ASSERT_EQ((1 << 15) | (1 << 2) |(1 << 8) | (1 << 10), flags);
}

TEST(BitFlagChecker, CheckMultipleBitFlagOnUint16)
{
    uint16_t flags = (1 << 15) | (1 << 2) | (1 << 8) | (1 << 10);
    ASSERT_TRUE(HasFlagSet(flags, 15, 2, 8, 10));
    ASSERT_TRUE(HasFlagSet(flags, 15, 2));
}

TEST(BitFlagChecker, CheckSingleBitFlagOnUint16)
{
    uint16_t flags = (1 << 15) | (1 << 2) | (1 << 8) | (1 << 10);
    ASSERT_TRUE(HasFlagSet(flags, 15));
}

TEST(BitFlagChecker, CheckMultipleBitFlagOnUint8)
{
    uint16_t flags = (1 << 5) | (1 << 2) | (1 << 8) | (1 << 1);
    ASSERT_TRUE(HasFlagSet(flags, 5, 2, 8, 1));
    ASSERT_TRUE(HasFlagSet(flags, 5, 2));
}

TEST(BitFlagChecker, CheckSingleBitFlagOnUint8)
{
    uint16_t flags = (1 << 5) | (1 << 2) | (1 << 8) | (1 << 1);
    ASSERT_TRUE(HasFlagSet(flags, 5));
}
