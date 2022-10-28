#include "gtest/gtest.h"
#include "libEmbedded/bits/Extracting.h"

using libEmbedded::bits::ExtractBits;

TEST(BitValueCombineHelpers, ExtractToManyBits)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kResul = 0b00000101;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 5, 8));
}

TEST(BitValueCombineHelpers, ExtractBitsAfterEnd)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kResul = 0x00;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 10, 4));
}

TEST(BitValueCombineHelpers, ExtractBitsInside)
{
    const uint8_t kVal1 = 0b11101010;
    const uint8_t kResul = 0b101;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 3, 3));
}
