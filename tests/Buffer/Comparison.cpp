#include <gtest/gtest.h>
#include "libEmbedded/Buffer.h"

constexpr size_t kBufferSize = 5;
using libEmbedded::Buffer;
using T = uint8_t;
using BufferT = Buffer<T, kBufferSize>;

template<typename TBufferData>
class BufferComparison : public ::testing::Test
{
protected:
    typename TBufferData::BufferAType bufferA;
};

struct BufferWithEqualSize
{
    static constexpr size_t kBufferBSize = kBufferSize;
    using BufferAType = Buffer<T, kBufferSize>;
    using BufferBType = Buffer<T, kBufferBSize>;
};

struct BufferWithInequalSize
{
    static constexpr size_t kBufferBSize = kBufferSize * 2;
    using BufferAType = Buffer<T, kBufferSize>;
    using BufferBType = Buffer<T, kBufferBSize>;
};

using TestBufferTypes = ::testing::Types<BufferWithEqualSize, BufferWithInequalSize>;

TYPED_TEST_SUITE(BufferComparison, TestBufferTypes);

TYPED_TEST(BufferComparison, CompareEqualWithInequalSizeBuffers)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    ASSERT_FALSE(this->bufferA == bufferB);
}

TYPED_TEST(BufferComparison, CompareEqualWithEqualSizeBuffersButDifferentContent)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    bufferB.Add(13);
    ASSERT_FALSE(this->bufferA == bufferB);
}

TYPED_TEST(BufferComparison, CompareEqualWithFullButDifferentContent)
{
    typename TypeParam::BufferBType bufferB;
    for (size_t i = 0; i < kBufferSize; i++)
    {
        this->bufferA.Add(10 + i);
    }
    for (size_t i = 0; i < TypeParam::kBufferBSize; i++)
    {
        bufferB.Add(20 + i);
    }
    ASSERT_FALSE(this->bufferA == bufferB);
}

TYPED_TEST(BufferComparison, CompareEqualWithEqualContent)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    bufferB.Add(11);
    ASSERT_TRUE(this->bufferA == bufferB);
}

TYPED_TEST(BufferComparison, CompareEqualWithEmpty)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    ASSERT_FALSE(this->bufferA == bufferB);
}

TYPED_TEST(BufferComparison, CompareEqualWithItSelf)
{
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    ASSERT_TRUE(this->bufferA == this->bufferA);
}



TYPED_TEST(BufferComparison, CompareInequalWithInequalSizeBuffers)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    ASSERT_TRUE(this->bufferA != bufferB);
}

TYPED_TEST(BufferComparison, CompareInequalWithEqualSizeBuffersButDifferentContent)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    bufferB.Add(13);
    ASSERT_TRUE(this->bufferA != bufferB);
}

TYPED_TEST(BufferComparison, CompareInequalWithFullButDifferentContent)
{
    typename TypeParam::BufferBType bufferB;
    for (size_t i = 0; i < kBufferSize; i++)
    {
        this->bufferA.Add(10 + i);
    }
    for (size_t i = 0; i < TypeParam::kBufferBSize; i++)
    {
        bufferB.Add(20 + i);
    }
    ASSERT_TRUE(this->bufferA != bufferB);
}

TYPED_TEST(BufferComparison, CompareInequalWithEqualContent)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    bufferB.Add(10);
    bufferB.Add(11);
    ASSERT_FALSE(this->bufferA != bufferB);
}

TYPED_TEST(BufferComparison, CompareInequalWithEmpty)
{
    typename TypeParam::BufferBType bufferB;
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    ASSERT_TRUE(this->bufferA != bufferB);
}

TYPED_TEST(BufferComparison, CompareInequalWithItSelf)
{
    this->bufferA.Add(10);
    this->bufferA.Add(11);
    ASSERT_FALSE(this->bufferA != this->bufferA);
}
