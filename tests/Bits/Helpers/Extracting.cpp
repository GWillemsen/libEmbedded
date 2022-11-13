#include "gtest/gtest.h"
#include "libEmbedded/bits/Extracting.h"

using libEmbedded::bits::ExtractBits;
using libEmbedded::bits::ExtractValues;

TEST(BitExtraction, ExtractToManyBits)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kResul = 0b00000101;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 5, 8));
}

TEST(BitExtraction, ExtractBitsAfterEnd)
{
    const uint8_t kVal1 = 0b10101010;
    const uint8_t kResul = 0x00;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 10, 4));
}

TEST(BitExtraction, ExtractBitsInside)
{
    const uint8_t kVal1 = 0b11101010;
    const uint8_t kResul = 0b101;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 3, 3));
}

TEST(BitExtraction, ExtractBitsAtUint64Top)
{
    const uint64_t kVal1 = 0xAABBCCDDEEFF1122;
    const uint8_t kResul = 0xAA;
    EXPECT_EQ(kResul, ExtractBits(kVal1, 56, 8));
}

TEST(BitExtraction, Extract1Value)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected = 0xA9;
    uint8_t value;
    ExtractValues(kBaseValue, value, 4, 8);
    EXPECT_EQ(kExpected, value);
}

TEST(BitExtraction, Extract1ValueOutOfRange)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected = 0x0;
    uint8_t value;
    ExtractValues(kBaseValue, value, 16, 8);
    EXPECT_EQ(kExpected, value);
}

TEST(BitExtraction, Extract2Values)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected1 = 0xA9;
    constexpr uint8_t kExpected2 = 0x7D;
    uint8_t value1;
    uint8_t value2;
    ExtractValues(kBaseValue, value1, 4, 8, value2, 9, 7);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
}

TEST(BitExtraction, Extract2ValuesReverseExtractBitOrder)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected1 = 0xA9;
    constexpr uint8_t kExpected2 = 0x7D;
    uint8_t value1;
    uint8_t value2;
    ExtractValues(kBaseValue, value2, 9, 7, value1, 4, 8);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
}

TEST(BitExtraction, Extract2Value1OutOfRange)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected1 = 0x0;
    constexpr uint8_t kExpected2 = 0x7D;
    uint8_t value1;
    uint8_t value2;
    ExtractValues(kBaseValue, value1, 16, 8, value2, 9, 7);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
}

TEST(BitExtraction, Extract2Value1OutOfRangeUint32_t)
{
    constexpr uint32_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected1 = 0x0;
    constexpr uint8_t kExpected2 = 0x7D;
    uint8_t value1;
    uint8_t value2;
    ExtractValues(kBaseValue, value1, 32, 8, value2, 9, 7);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
}

TEST(BitExtraction, Extract2ValueBothOutOfRange)
{
    constexpr uint16_t kBaseValue = 0xFA91;
    constexpr uint8_t kExpected1 = 0x0;
    constexpr uint8_t kExpected2 = 0x0;
    uint8_t value1;
    uint8_t value2;
    ExtractValues(kBaseValue, value1, 16, 8, value2, 24, 2);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
}

TEST(BitExtraction, Extract3Values)
{
    constexpr uint32_t kBaseValue = 0xBAFA91;
    constexpr uint8_t kExpected1 = 0xA9;
    constexpr uint8_t kExpected2 = 0x7D;
    constexpr uint16_t kExpected3 = 0xFA9;
    uint8_t value1;
    uint8_t value2;
    uint16_t value3;
    ExtractValues(kBaseValue, value1, 4, 8, value2, 9, 7, value3, 4, 12);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
    EXPECT_EQ(kExpected3, value3);
}

TEST(BitExtraction, Extract3ValuesReverseExtractBitOrder)
{
    constexpr uint32_t kBaseValue = 0xBAFA91;
    constexpr uint8_t kExpected1 = 0xA9;
    constexpr uint8_t kExpected2 = 0x7D;
    constexpr uint16_t kExpected3 = 0x7D4;
    uint8_t value1;
    uint8_t value2;
    uint16_t value3;
    ExtractValues(kBaseValue, value3, 5, 11, value2, 9, 7, value1, 4, 8);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
    EXPECT_EQ(kExpected3, value3);
}

TEST(BitExtraction, Extract3Value1OutOfRange)
{
    constexpr uint32_t kBaseValue = 0xBAFA91;
    constexpr uint8_t kExpected1 = 0x0;
    constexpr uint8_t kExpected2 = 0x7D;
    constexpr uint16_t kExpected3 = 0x7D4;
    uint8_t value1;
    uint8_t value2;
    uint16_t value3;
    ExtractValues(kBaseValue, value1, 32, 8, value2, 9, 7, value3, 5, 11);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
    EXPECT_EQ(kExpected3, value3);
}

TEST(BitExtraction, Extract3Value2OutOfRange)
{
    constexpr uint32_t kBaseValue = 0xBAFA91;
    constexpr uint8_t kExpected1 = 0x0;
    constexpr uint8_t kExpected2 = 0x0;
    constexpr uint16_t kExpected3 = 0x7D4;
    uint8_t value1;
    uint8_t value2;
    uint16_t value3;
    ExtractValues(kBaseValue, value1, 32, 8, value2, 48, 2, value3, 5, 11);
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
    EXPECT_EQ(kExpected3, value3);
}

TEST(BitExtraction, ExtractBytesFromUint64_t)
{
    constexpr uint64_t kBaseValue = 0xAABBCCDDEEFF1122;
    constexpr uint8_t kExpected1 = 0xAA;
    constexpr uint8_t kExpected2 = 0xBB;
    constexpr uint8_t kExpected3 = 0xCC;
    constexpr uint8_t kExpected4 = 0xDD;
    constexpr uint8_t kExpected5 = 0xEE;
    constexpr uint8_t kExpected6 = 0xFF;
    constexpr uint8_t kExpected7 = 0x11;
    constexpr uint8_t kExpected8 = 0x22;
    uint8_t value1;
    uint8_t value2;
    uint8_t value3;
    uint8_t value4;
    uint8_t value5;
    uint8_t value6;
    uint8_t value7;
    uint8_t value8;
    ExtractValues(kBaseValue, 
        value1, 56, 8,
        value2, 48, 8,
        value3, 40, 8,
        value4, 32, 8,
        value5, 24, 8,
        value6, 16, 8,
        value7, 8, 8,
        value8, 0, 8
        );
    EXPECT_EQ(kExpected1, value1);
    EXPECT_EQ(kExpected2, value2);
    EXPECT_EQ(kExpected3, value3);
    EXPECT_EQ(kExpected4, value4);
    EXPECT_EQ(kExpected5, value5);
    EXPECT_EQ(kExpected6, value6);
    EXPECT_EQ(kExpected7, value7);
    EXPECT_EQ(kExpected8, value8);
}

TEST(BitExtraction, ExtractTopByteFromUint64_t)
{
    constexpr uint64_t kBaseValue = 0xAABBCCDDEEFF1122;
    constexpr uint8_t kExpected1 = 0xAA;
    uint8_t value1;
    ExtractValues(kBaseValue, 
        value1, 56, 8
        );
    EXPECT_EQ(kExpected1, value1);
}
