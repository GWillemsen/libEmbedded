#include <gtest/gtest.h>
#include "libEmbedded/Buffer.h"

constexpr size_t kBufferSize = 5;
using libEmbedded::Buffer;
using T = uint8_t;
using BufferT = Buffer<T, kBufferSize>;

class BufferIterators : public ::testing::Test
{
protected:
    BufferT buffer;
};

TEST_F(BufferIterators, ReadStandardBeginWithStandardEnd)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    this->buffer.Add(4);
    this->buffer.Add(5);
    BufferT::iterator begin = this->buffer.begin();
    EXPECT_EQ(1, *begin);
    ASSERT_NE(begin, this->buffer.end());
    begin++;

    EXPECT_EQ(2, *begin);
    ASSERT_NE(begin, this->buffer.end());
    begin++;
    EXPECT_EQ(3, *begin);
    ASSERT_NE(begin, this->buffer.end());
    begin++;
    EXPECT_EQ(4, *begin);
    ASSERT_NE(begin, this->buffer.end());
    begin++;
    EXPECT_EQ(5, *begin);
    begin++;
    ASSERT_EQ(begin, this->buffer.end());
}

TEST_F(BufferIterators, ReadConstBufferBeginWithEnd)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    this->buffer.Add(4);
    this->buffer.Add(5);
    const BufferT& cBuffer = this->buffer;
    BufferT::const_iterator begin = cBuffer.begin();
    EXPECT_EQ(1, *begin);
    ASSERT_NE(begin, cBuffer.end());
    begin++;

    EXPECT_EQ(2, *begin);
    ASSERT_NE(begin, cBuffer.end());
    begin++;
    EXPECT_EQ(3, *begin);
    ASSERT_NE(begin, cBuffer.end());
    begin++;
    EXPECT_EQ(4, *begin);
    ASSERT_NE(begin, cBuffer.end());
    begin++;
    EXPECT_EQ(5, *begin);
    begin++;
    ASSERT_EQ(begin, cBuffer.end());
}

TEST_F(BufferIterators, ReadConstBeginWithConstEnd)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    this->buffer.Add(4);
    this->buffer.Add(5);
    const BufferT& cBuffer = this->buffer;
    BufferT::const_iterator begin = cBuffer.cbegin();
    EXPECT_EQ(1, *begin);
    ASSERT_NE(begin, cBuffer.cend());
    begin++;

    EXPECT_EQ(2, *begin);
    ASSERT_NE(begin, cBuffer.cend());
    begin++;
    EXPECT_EQ(3, *begin);
    ASSERT_NE(begin, cBuffer.cend());
    begin++;
    EXPECT_EQ(4, *begin);
    ASSERT_NE(begin, cBuffer.cend());
    begin++;
    EXPECT_EQ(5, *begin);
    begin++;
    ASSERT_EQ(begin, cBuffer.cend());
}

TEST_F(BufferIterators, ModifyBegin)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    this->buffer.Add(4);
    this->buffer.Add(5);
    BufferT::iterator it = this->buffer.begin();

    it += 2;
    *it = 10;
    ASSERT_EQ(1, this->buffer.GetItem(0));
    ASSERT_EQ(2, this->buffer.GetItem(1));
    ASSERT_EQ(10, this->buffer.GetItem(2));
    ASSERT_EQ(4, this->buffer.GetItem(3));
    ASSERT_EQ(5, this->buffer.GetItem(4));
}

TEST_F(BufferIterators, ModifyEnd)
{
    this->buffer.Add(1);
    this->buffer.Add(2);
    this->buffer.Add(3);
    this->buffer.Add(4);
    this->buffer.Add(5);
    BufferT::iterator it = this->buffer.end();

    it -= 2;
    *it = 10;
    ASSERT_EQ(1, this->buffer.GetItem(0));
    ASSERT_EQ(2, this->buffer.GetItem(1));
    ASSERT_EQ(3, this->buffer.GetItem(2));
    ASSERT_EQ(10, this->buffer.GetItem(3));
    ASSERT_EQ(5, this->buffer.GetItem(4));
}
