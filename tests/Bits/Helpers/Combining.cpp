#include "gtest/gtest.h"
#include "libEmbedded/bits/Combining.h"

using libEmbedded::bits::CombineBitValues;
using libEmbedded::bits::SetBits;

TEST(BitValueCombineHelpers, CombineBitValue)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kVal2 = 0b1010010;
    const uint8_t kResul = 0b01001010;
    EXPECT_EQ(kResul, (CombineBitValues<uint8_t,uint8_t,uint16_t>(kVal1, kVal2, 0, 3, 1, 5)));
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

TEST(BitSetter, Set2MassiveValues)
{
    constexpr uint64_t kInitial =  0x0000000000AABBAA;
    constexpr uint64_t kExpected = 0x0000FFBBAAAA00AA;
    constexpr uint64_t kInput1 =   0x0000FFBBA;
    constexpr uint64_t kInput2 = 0xCAAAA00AA;
    constexpr auto kResult = SetBits<uint64_t, uint64_t>(kInitial, kInput1, 28, 40, kInput2, 0, 36);
    EXPECT_EQ(kExpected, kResult);
}
TEST(BitSetter, Set1AtMassiveEnd)
{
    constexpr uint64_t kInitial =  0x0000000000000000;
    constexpr uint64_t kExpected = 0xAA00000000000000;
    constexpr uint64_t kInput1 =   0xAA;
    // constexpr uint64_t kInput2 = 0xCAAAA00AA;
    constexpr auto kResult = SetBits<uint64_t, uint64_t>(kInitial, kInput1, 56, 8);
    EXPECT_EQ(kExpected, kResult);
}

TEST(BitSetter, Set4ValuesToMakeMassive)
{
    constexpr uint64_t kInitial =  0x0000000000AABBAA;
    constexpr uint64_t kExpected = 0xCCBBFFAA00AABBAA;
    constexpr uint64_t kInput4 = 0xCC;
    constexpr uint64_t kInput3 = 0xBB;
    constexpr uint64_t kInput2 = 0xFF;
    constexpr uint64_t kInput1 = 0xAA;
    constexpr auto kResult = SetBits<uint64_t, uint64_t>(kInitial, kInput1, 32, 8, kInput2, 40, 8, kInput3, 48, 8, kInput4, 56, 8);
    EXPECT_EQ(kExpected, kResult);
}