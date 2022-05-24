#include "gtest/gtest.h"
#include "limits.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::MoveWithOffset;

class MoveWithBitOffset : public ::testing::Test {
protected:
    static constexpr size_t kBufferASize = 10;
    static constexpr size_t kBufferBSize = 10;
    char bufferA[kBufferASize];
    const char checkBuffer[kBufferBSize];

public:
    MoveWithBitOffset() : bufferA{1,2,3,4,5,6,7,8,9}, checkBuffer{1,2,3,4,5,6,7,8,9} //, bufferB{1,2,4,8,16,32,64,128,256,512}
    {
    }
};


TEST(BitHelpers, MoveWithBitOffsetNullPtrs)
{
    MoveWithOffset(nullptr, 2, nullptr, 5, 16);
}

TEST_F(MoveWithBitOffset, SameBufferSameOffset)
{
    MoveWithOffset(bufferA, 2, bufferA, 2, kBufferASize * CHAR_MAX);
    EXPECT_EQ(checkBuffer[0], bufferA[0]);
    EXPECT_EQ(checkBuffer[1], bufferA[1]);
    EXPECT_EQ(checkBuffer[2], bufferA[2]);
    EXPECT_EQ(checkBuffer[3], bufferA[3]);
    EXPECT_EQ(checkBuffer[4], bufferA[4]);
    EXPECT_EQ(checkBuffer[5], bufferA[5]);
    EXPECT_EQ(checkBuffer[6], bufferA[6]);
    EXPECT_EQ(checkBuffer[7], bufferA[7]);
    EXPECT_EQ(checkBuffer[8], bufferA[8]);
    EXPECT_EQ(checkBuffer[9], bufferA[9]);
}

TEST(MoveWithBitOffsets, SameBuffer2ByteLocal)
{
    char bufferB[2] = { 0x00, (char)(0xFF)};
    MoveWithOffset(bufferB, 0, bufferB + 1, 0, 1 * CHAR_BIT);
    EXPECT_EQ(bufferB[0], ((char)0xFF));
    EXPECT_EQ(bufferB[1], ((char)0xFF));
}

TEST_F(MoveWithBitOffset, SameBufferByteOffset)
{
    char bufferB[2] = { 0x00, (char)(0xFF)};
    MoveWithOffset(bufferB, 0, bufferB + 1, 0, 1 * CHAR_BIT);
    EXPECT_EQ(checkBuffer[1], bufferA[0]);
    EXPECT_EQ(checkBuffer[2], bufferA[1]);
    EXPECT_EQ(checkBuffer[3], bufferA[2]);
    EXPECT_EQ(checkBuffer[4], bufferA[3]);
    EXPECT_EQ(checkBuffer[5], bufferA[4]);
    EXPECT_EQ(checkBuffer[6], bufferA[5]);
    EXPECT_EQ(checkBuffer[7], bufferA[6]);
    EXPECT_EQ(checkBuffer[8], bufferA[7]);
    EXPECT_EQ(checkBuffer[9], bufferA[8]);
    EXPECT_EQ(checkBuffer[9], bufferA[9]);
}
