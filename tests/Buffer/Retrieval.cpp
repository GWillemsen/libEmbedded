#include <gtest/gtest.h>
#include "libEmbedded/Buffer.h"

constexpr size_t kBufferSize = 5;
using libEmbedded::Buffer;
using T = uint8_t;
using BufferT = Buffer<T, kBufferSize>;

class BufferRetrieval : public ::testing::Test
{
protected:
    BufferT buffer;
};

TEST_F(BufferRetrieval, GetItemOnConstBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 12;
    const BufferT& cBuffer = this->buffer;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, cBuffer.GetItem(0));
    ASSERT_EQ(kValue2, cBuffer.GetItem(1));
}

TEST_F(BufferRetrieval, GetItemOnBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, this->buffer.GetItem(0));
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
}

TEST_F(BufferRetrieval, GetItemWriteOnBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 13;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, this->buffer.GetItem(0));
    this->buffer.GetItem(0) = kValue3;
    ASSERT_EQ(kValue3, this->buffer.GetItem(0));
}

TEST_F(BufferRetrieval, GetItemOnBufferAndThenChange)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 15;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    T& val = this->buffer.GetItem(0);
    ASSERT_EQ(kValue1, val);
    this->buffer.GetItem(0) = kValue3;
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
    ASSERT_EQ(kValue3, val);
}

TEST_F(BufferRetrieval, GetItemOnConstBufferAndThenChange)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 15;

    const BufferT& cBuffer = this->buffer;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    const T& val = cBuffer.GetItem(0);
    ASSERT_EQ(kValue1, val);
    this->buffer.GetItem(0) = kValue3;
    ASSERT_EQ(kValue2, this->buffer.GetItem(1));
    ASSERT_EQ(kValue3, val);
}


TEST_F(BufferRetrieval, IndexOperatorOnConstBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 12;
    const BufferT& cBuffer = this->buffer;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, cBuffer[0]);
    ASSERT_EQ(kValue2, cBuffer[1]);
}

TEST_F(BufferRetrieval, IndexOperatorOnBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, this->buffer[0]);
    ASSERT_EQ(kValue2, this->buffer[1]);
}

TEST_F(BufferRetrieval, IndexOperatorWriteOnBuffer)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 13;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    ASSERT_EQ(kValue1, this->buffer[0]);
    this->buffer[0] = kValue3;
    ASSERT_EQ(kValue3, this->buffer[0]);
}

TEST_F(BufferRetrieval, IndexOperatorOnBufferAndThenChange)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 15;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    T& val = this->buffer[0];
    ASSERT_EQ(kValue1, val);
    this->buffer[0] = kValue3;
    ASSERT_EQ(kValue2, this->buffer[1]);
    ASSERT_EQ(kValue3, val);
}

TEST_F(BufferRetrieval, IndexOperatorOnConstBufferAndThenChange)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 11;
    constexpr T kValue3 = 15;

    const BufferT& cBuffer = this->buffer;

    this->buffer.Add(kValue1);
    this->buffer.Add(kValue2);
    const T& val = cBuffer[0];
    ASSERT_EQ(kValue1, val);
    this->buffer[0] = kValue3;
    ASSERT_EQ(kValue2, this->buffer[1]);
    ASSERT_EQ(kValue3, val);
}
