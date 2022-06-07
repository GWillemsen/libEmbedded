#include "gtest/gtest.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::CreateFlagSet;
using libEmbedded::bits::HasFlagSet;

class BitMaskCreatorFixture : public ::testing::Test {};

TEST_F(BitMaskCreatorFixture, SinglePositionArgInRangeOfType)
{
    uint8_t flags = CreateFlagSet<uint8_t, 5>();
    ASSERT_EQ((1 << 5), flags);
}

TEST_F(BitMaskCreatorFixture, SinglePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17>();
    ASSERT_EQ(0, flags);
}

TEST_F(BitMaskCreatorFixture, TwoPositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST_F(BitMaskCreatorFixture, TwoPositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 15>();
    ASSERT_EQ((1 << 15), flags);
}

TEST_F(BitMaskCreatorFixture, TwoPositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 15, 2>();
    ASSERT_EQ((1 << 15) | (1 << 2), flags);
}

TEST_F(BitMaskCreatorFixture, MultiplePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST_F(BitMaskCreatorFixture, MultiplePositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19, 8, 10, 16>();
    ASSERT_EQ((1 << 8) | (1 << 10), flags);
}

TEST_F(BitMaskCreatorFixture, MultiplePositionArgInRange)
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
