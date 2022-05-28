#include "gtest/gtest.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::CombineBitValues;
using libEmbedded::bits::GetCombinedValue;
using libEmbedded::bits::ExtractBits;
using libEmbedded::bits::GetBitSize;

TEST(BitValueCombineHelpers, CombineBitValue)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kVal2 = 0b1010010;
    const uint8_t kResul = 0b01001010;
    EXPECT_EQ(kResul, (CombineBitValues<uint8_t,uint8_t,uint16_t>(kVal1, kVal2, 0, 3, 1, 5)));
}

TEST(BitValueCombineHelpers, GetCombinedValueToManyBits)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kVal2 = 0b01010010;
    const uint16_t kResul = kVal1 | (kVal2 << 8);
    EXPECT_EQ(kResul, GetCombinedValue(kVal1, kVal2, 0, 32));
}

TEST(BitValueCombineHelpers, GetCombinedValueToLargeStartBit)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kVal2 = 0b1010010;
    const uint16_t kResul = 0x00;
    EXPECT_EQ(kResul, GetCombinedValue(kVal1, kVal2, 17, 15));
}

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
