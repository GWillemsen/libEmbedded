#include "gtest/gtest.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::SetBits;

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
