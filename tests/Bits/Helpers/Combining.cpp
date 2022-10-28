#include "gtest/gtest.h"
#include "libEmbedded/bits/Combining.h"

using libEmbedded::bits::CombineBitValues;
using libEmbedded::bits::GetCombinedValue;
using libEmbedded::bits::SetBits;

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

TEST(BitSetter, Set1ValueWithInitial)
{
    constexpr uint16_t kInitial = 0b1100010001;
    constexpr uint16_t kExpected = 0b1111001101;
    constexpr uint16_t kInput = 0b110011;
    constexpr auto kResult = SetBits<uint16_t, uint16_t>(kInitial, kInput, 2, 6);
    EXPECT_EQ(kExpected, kResult);
}

TEST(BitSetter, Set1ValueWithBitsOutsizeLengthWithInitial)
{
    constexpr uint16_t kInitial = 0b1100010000;
    constexpr uint16_t kExpected = 0b1100001100;
    constexpr uint16_t kInput = 0b110011;
    constexpr auto kResult = SetBits<uint16_t, uint16_t>(kInitial, kInput, 2, 3);
    EXPECT_EQ(kExpected, kResult);
}

TEST(BitSetter, Set2Values)
{
    constexpr uint16_t kInitial = 0b1101010001;
    constexpr uint16_t kExpected = 0b1110110101;
    constexpr uint16_t kInput1 = 0b11;
    constexpr uint16_t kInput2 = 0b100001;
    constexpr auto kResult = SetBits<uint16_t, uint16_t>(kInitial, kInput1, 4, 2, kInput2, 2, 6);
    EXPECT_EQ(kExpected, kResult);
}

TEST(BitSetter, Set2ValuesWithBitsOutsizeLength)
{
    constexpr uint16_t kInitial =  0b1101010001;
    constexpr uint16_t kExpected = 0b1110110101;
    constexpr uint16_t kInput1 = 0b110111;
    constexpr uint16_t kInput2 = 0b111100001;
    constexpr auto kResult = SetBits<uint16_t, uint16_t>(kInitial, kInput1, 4, 2, kInput2, 2, 6);
    EXPECT_EQ(kExpected, kResult);
}
TEST(BitSetter, Set3Values)
{
    constexpr uint16_t kInitial =    0b1101010001;
    constexpr uint16_t kExpected = 0b100010110100;
    constexpr uint16_t kInput1 = 0b11;
    constexpr uint16_t kInput2 = 0b100001;
    constexpr uint16_t kInput3 = 0b100000000000;
    constexpr auto kResult = SetBits<uint16_t, uint16_t>(kInitial, kInput1, 4, 2, kInput2, 2, 6, kInput3, 0, 12);
    EXPECT_EQ(kExpected, kResult);
}

TEST(BitSetter, Set3ValuesWithBitsOutsizeLength)
{
    constexpr uint16_t kInitial =    0b1101010001;
    constexpr uint16_t kExpected = 0b100010110100;
    constexpr uint16_t kInput1 =   0b110111;
    constexpr uint16_t kInput2 =  0b111100001;
    constexpr uint16_t kInput3 = 0b100000000000;
    constexpr auto kResult = SetBits<uint16_t>(kInitial, kInput1, 4, 2, kInput2, 2, 6, kInput3, 0, 12);
    EXPECT_EQ(kExpected, kResult);
}
