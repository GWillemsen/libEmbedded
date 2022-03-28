#include <gtest/gtest.h>
#include "libEmbedded/Buffer.h"

constexpr size_t kBufferSize = 5;
using libEmbedded::Buffer;
using T = uint8_t;
using BufferT = Buffer<T, kBufferSize>;

class BufferAssignmentAndConstructor : public ::testing::Test
{
protected:
};

TEST_F(BufferAssignmentAndConstructor, AssignmentAndOneModifiedAfter)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 15;
    BufferT bufferA;
    BufferT bufferB;
    bufferA.Add(kValue1);
    bufferB = bufferA;
    bufferA.Add(kValue2);
    ASSERT_EQ(2, bufferA.Size());
    ASSERT_EQ(1, bufferB.Size());
    ASSERT_EQ(kValue1, bufferA[0]);
    ASSERT_EQ(kValue2, bufferA[1]);
    ASSERT_EQ(kValue1, bufferB[0]);
}

TEST_F(BufferAssignmentAndConstructor, CopyConstructorAndThenModifiedAfter)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 10;
    constexpr T kValue3 = 10;
    BufferT bufferA;
    bufferA.Add(kValue1);
    BufferT bufferB(bufferA);
    bufferA.Add(kValue2);
    bufferB.Add(kValue3);
    ASSERT_EQ(2, bufferA.Size());
    ASSERT_EQ(2, bufferB.Size());
    ASSERT_EQ(kValue1, bufferA[0]);
    ASSERT_EQ(kValue2, bufferA[1]);
    ASSERT_EQ(kValue1, bufferB[0]);
    ASSERT_EQ(kValue3, bufferB[1]);
}

TEST_F(BufferAssignmentAndConstructor, AssignmentReturnsItSelf)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 15;
    BufferT bufferA;
    BufferT bufferB;
    bufferA.Add(kValue1);
    BufferT& result = (bufferB = bufferA);
    ASSERT_EQ(&bufferB, &result);    
}

TEST_F(BufferAssignmentAndConstructor, CopyConstructorFromDifferentSizeAndThenModifiedAfter)
{
    constexpr T kValue1 = 10;
    constexpr T kValue2 = 10;
    constexpr T kValue3 = 10;
    Buffer<T, 5> bufferA;
    bufferA.Add(kValue1);
    Buffer<T, 7> bufferB(bufferA);
    bufferA.Add(kValue2);
    bufferB.Add(kValue3);
    ASSERT_EQ(2, bufferA.Size());
    ASSERT_EQ(2, bufferB.Size());
    ASSERT_EQ(kValue1, bufferA[0]);
    ASSERT_EQ(kValue2, bufferA[1]);
    ASSERT_EQ(kValue1, bufferB[0]);
    ASSERT_EQ(kValue3, bufferB[1]);
}
