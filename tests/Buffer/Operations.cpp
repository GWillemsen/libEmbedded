#include <gtest/gtest.h>
#include "libEmbedded/Buffer.h"

constexpr size_t kBufferSize = 5;

using libEmbedded::Buffer;
using T = uint8_t;
using BufferT = Buffer<T, kBufferSize>;

class BufferOperationsFixture : public ::testing::Test
{
protected:
    BufferT buffer;
};

TEST_F(BufferOperationsFixture, PushTwoItemsAndGetItemCorrespond)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 20;
    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, this->buffer.GetItem(0));
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
}

TEST_F(BufferOperationsFixture, PushMoreThanSize)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 20;
    constexpr T kValue3 = 30;
    constexpr T kValue4 = 40;
    constexpr T kValue5 = 50;
    constexpr T kValue6 = 60;
    constexpr T kValue7 = 70;
    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    this->buffer.Add(kValue3);
    this->buffer.Add(kValue4);
    this->buffer.Add(kValue5);
    this->buffer.Add(kValue6);
    this->buffer.Add(kValue7);
    ASSERT_EQ(kValue3, this->buffer.GetItem(0));
    ASSERT_EQ(kValue4, this->buffer.GetItem(1));
    ASSERT_EQ(kValue5, this->buffer.GetItem(2));
    ASSERT_EQ(kValue6, this->buffer.GetItem(3));
    ASSERT_EQ(kValue7, this->buffer.GetItem(4));
}

TEST_F(BufferOperationsFixture, RemoveFromEmptyBuffer)
{
    EXPECT_EQ(0, this->buffer.Size());
    this->buffer.Remove(10);
    ASSERT_EQ(0, this->buffer.Size());
}

TEST_F(BufferOperationsFixture, RemoveValuesFromBufferButLeaveSome)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    EXPECT_EQ(3, this->buffer.Size());
    this->buffer.Remove(2);
    ASSERT_EQ(1, this->buffer.Size());
    ASSERT_EQ(3, this->buffer.GetItem(0));
}

TEST_F(BufferOperationsFixture, RemoveWholeBufferAtOnce)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    EXPECT_EQ(3, this->buffer.Size());
    this->buffer.Remove(3);
    ASSERT_EQ(0, this->buffer.Size());
}

TEST_F(BufferOperationsFixture, RemoveSomeBufferAndThenRemainderAtOnce)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    EXPECT_EQ(3, this->buffer.Size());
    this->buffer.Remove(1);
    ASSERT_EQ(2, this->buffer.Size());
    EXPECT_EQ(2, this->buffer.GetItem(0));
    EXPECT_EQ(3, this->buffer.GetItem(1));
    this->buffer.Remove(2);
    ASSERT_EQ(0, this->buffer.Size());
}

TEST_F(BufferOperationsFixture, AddRangeToExistingWithinLeftoverSpace)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 13;
    constexpr T kValue3 = 18;
    this->buffer.Add(kValue1);
    T values[2] = {kValue2, kValue3};
    this->buffer.AddRange(values, sizeof(values) / sizeof(T));
    ASSERT_EQ(3, this->buffer.Size());
    ASSERT_EQ(kValue1, this->buffer.GetItem(0));
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
    ASSERT_EQ(kValue3, this->buffer.GetItem(2));
}

TEST_F(BufferOperationsFixture, AddRangeInEmptyWithinLeftoverSpace)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 20;
    T values[2] = {kValue1, kValue2};
    this->buffer.AddRange(values, sizeof(values) / sizeof(T));
    // ASSERT_EQ(2, this->buffer.Size());
    ASSERT_LT(1, this->buffer.Size());
    EXPECT_EQ(kValue1, this->buffer.GetItem(0));
    ASSERT_EQ(2, this->buffer.Size());
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
}

TEST_F(BufferOperationsFixture, AddRangeInEmptyWithMoreThanLeftoverSpace)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 12;
    constexpr T kValue4 = 13;
    constexpr T kValue5 = 20;
    constexpr T kValue6 = 30;
    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    this->buffer.Add(kValue3);
    this->buffer.Add(kValue4);
    T values[2] = {kValue5, kValue6};
    this->buffer.AddRange(values, sizeof(values) / sizeof(T));
    ASSERT_LT(1, this->buffer.Size());
    EXPECT_EQ(kValue2, this->buffer.GetItem(0));
    ASSERT_LT(2, this->buffer.Size());
    EXPECT_EQ(kValue3, this->buffer.GetItem(1));
    ASSERT_LT(3, this->buffer.Size());
    EXPECT_EQ(kValue4, this->buffer.GetItem(2));
    ASSERT_LT(4, this->buffer.Size());
    EXPECT_EQ(kValue5, this->buffer.GetItem(3));
    ASSERT_EQ(5, this->buffer.Size());
    ASSERT_EQ(kValue6, this->buffer.GetItem(4));
}

TEST_F(BufferOperationsFixture, AddRangeInEmptyWithMoreThanTotalCapacity)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 12;
    constexpr T kValue4 = 13;
    constexpr T kValue5 = 20;
    constexpr T kValue6 = 30;
    constexpr T kValue7 = 35;
    constexpr T kValue8 = 40;
    constexpr T kValue9 = 40;
    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    T values[7] = {kValue3, kValue4, kValue5, kValue6, kValue7, kValue8, kValue9};
    this->buffer.AddRange(values, sizeof(values) / sizeof(T));
    // swap expect assert and add gt
    ASSERT_LT(1, this->buffer.Size());
    EXPECT_EQ(kValue5, this->buffer.GetItem(0));
    ASSERT_LT(2, this->buffer.Size());
    EXPECT_EQ(kValue6, this->buffer.GetItem(1));
    ASSERT_LT(3, this->buffer.Size());
    EXPECT_EQ(kValue7, this->buffer.GetItem(2));
    ASSERT_LT(4, this->buffer.Size());
    EXPECT_EQ(kValue8, this->buffer.GetItem(3));
    ASSERT_EQ(5, this->buffer.Size());
    EXPECT_EQ(kValue9, this->buffer.GetItem(4));
}

TEST(BufferOperations, RemoveRangeAndProperMemoryClear)
{
    /*
        This unit test arose from one of the applications I used this library in.
        The problem was that when the remove cleans up the buffer it also overwrites 
        size_t value indicating the number of bytes used from the buffer. This was 
        because it would start the memset 1 position to high. It would then also clear
        part of count to 0. After it did that it would still subtract the number of 
        bytes removed in the buffer from the value, resulting in a wrap around if enough
        of the size was overwritten.
        This was not visible in the other tests since there the buffer size was 5. So the
        compiler would pad the array to align with the word size, making space for the 
        overflow to happen and not disturb anything imporant.
    */

    Buffer<int, 10> buffer;
    for (int i = 0; i < 5; i++)
    {
        constexpr long value = 10;
        buffer.Add(value);
    }
    ASSERT_EQ(5, buffer.Size());
    buffer.Remove(1);
    EXPECT_EQ(12, buffer.Size());
}
