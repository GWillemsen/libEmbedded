#include "gtest/gtest.h"
#include "libEmbedded/bits/Flags.h"

using libEmbedded::bits::CreateFlagSet;
using libEmbedded::bits::HasFlagSet;

///
/// CreateFlagSet with template arguments
///

TEST(BitMaskingTemplateArgs, SinglePositionArgInRangeOfType)
{
    uint8_t flags = CreateFlagSet<uint8_t, 5>();
    ASSERT_EQ((1 << 5), flags);
}

TEST(BitMaskingTemplateArgs, SinglePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17>();
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingTemplateArgs, TwoPositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingTemplateArgs, TwoPositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 15>();
    ASSERT_EQ((1 << 15), flags);
}

TEST(BitMaskingTemplateArgs, TwoPositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 15, 2>();
    ASSERT_EQ((1 << 15) | (1 << 2), flags);
}

TEST(BitMaskingTemplateArgs, MultiplePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19>();
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingTemplateArgs, MultiplePositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 17, 18, 19, 8, 10, 16>();
    ASSERT_EQ((1 << 8) | (1 << 10), flags);
}

TEST(BitMaskingTemplateArgs, MultiplePositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t, 15, 2, 8, 10>();
    ASSERT_EQ((1 << 15) | (1 << 2) |(1 << 8) | (1 << 10), flags);
}

///
/// CreateFlagSet with regular arguments
///

TEST(BitMaskingValueArgs, SinglePositionArgInRangeOfType)
{
    uint8_t flags = CreateFlagSet<uint8_t>(5);
    ASSERT_EQ((1 << 5), flags);
}

TEST(BitMaskingValueArgs, SinglePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t>(17);
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingValueArgs, TwoPositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t>(17, 18, 19);
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingValueArgs, TwoPositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t>(17, 15);
    ASSERT_EQ((1 << 15), flags);
}

TEST(BitMaskingValueArgs, TwoPositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t>(15, 2);
    ASSERT_EQ((1 << 15) | (1 << 2), flags);
}

TEST(BitMaskingValueArgs, MultiplePositionArgOutRangeOfType)
{
    uint16_t flags = CreateFlagSet<uint16_t>(17, 18, 19);
    ASSERT_EQ(0, flags);
}

TEST(BitMaskingValueArgs, MultiplePositionArgOutRangeOfTypeSomeInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t>(17, 18, 19, 8, 10, 16);
    ASSERT_EQ((1 << 8) | (1 << 10), flags);
}

TEST(BitMaskingValueArgs, MultiplePositionArgInRange)
{
    uint16_t flags = CreateFlagSet<uint16_t>(15, 2, 8, 10);
    ASSERT_EQ((1 << 15) | (1 << 2) |(1 << 8) | (1 << 10), flags);
}

///
/// HasFlagSet unit tests
///

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
