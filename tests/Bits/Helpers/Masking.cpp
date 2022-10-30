#include "gtest/gtest.h"
#include "libEmbedded/bits/Masking.h"

using libEmbedded::bits::CreateMask;
using libEmbedded::bits::SetNrBits;

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

TEST(BitMaskCreatorFixture, CreateMask5WithOutOfRangeStart)
{
    uint32_t mask = CreateMask(5, 32);
    ASSERT_EQ(0x00, mask);
}

TEST(BitMaskCreatorFixture, SetNrBits10)
{
    uint16_t mask = SetNrBits<uint16_t>(10);
    ASSERT_EQ(0b1111111111, mask);
}

TEST(BitMaskCreatorFixture, SetNrBits5)
{
    uint16_t mask = SetNrBits<uint16_t>(5);
    ASSERT_EQ(0b11111, mask);
}
