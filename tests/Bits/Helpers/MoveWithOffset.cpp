#include "gtest/gtest.h"
#include "limits.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::MoveWithOffset;
using libEmbedded::bits::CombineBitValues;


class MoveWithBitOffset : public ::testing::Test {
protected:
    static constexpr size_t kBufferASize = 10;
    static constexpr size_t kBufferBSize = 10;
    char bufferA[kBufferASize];
    unsigned char bufferB[kBufferASize];
    const char checkBuffer[kBufferBSize];
    const unsigned char checkBufferB[kBufferBSize];

public:
    MoveWithBitOffset() : 
        bufferA{4, 1,2,3,4,5,6,7,8,9}, checkBuffer{4, 1,2,3,4,5,6,7,8,9}, 
        bufferB{1,2,4,8,16,32,64,128,CHAR_MAX,48}, checkBufferB{1,2,4,8,16,32,64,128,CHAR_MAX,48}
    {
    }
};

TEST(BitHelpers, MoveWithBitOffsetNullPtrs)
{
    MoveWithOffset(nullptr, 2, nullptr, 5, 16);
}

TEST_F(MoveWithBitOffset, DifferentBufferSameOffset)
{
    char bufferB[kBufferASize * 2] = { 0 };
    MoveWithOffset(bufferB, 2, bufferA, 2, (kBufferASize * CHAR_BIT) - 2);
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
    EXPECT_EQ(bufferA[0], bufferB[0]);
    EXPECT_EQ(bufferA[1], bufferB[1]);
    EXPECT_EQ(bufferA[2], bufferB[2]);
    EXPECT_EQ(bufferA[3], bufferB[3]);
    EXPECT_EQ(bufferA[4], bufferB[4]);
    EXPECT_EQ(bufferA[5], bufferB[5]);
    EXPECT_EQ(bufferA[6], bufferB[6]);
    EXPECT_EQ(bufferA[7], bufferB[7]);
    EXPECT_EQ(bufferA[8], bufferB[8]);
    EXPECT_EQ(bufferA[9], bufferB[9]);
}

TEST_F(MoveWithBitOffset, SameBufferSameOffset)
{
    MoveWithOffset(bufferA, 2, bufferA, 2, kBufferASize * CHAR_BIT);
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

TEST(MoveWithBitOffsets, TwoByteLocalBufferShift1Byte)
{
    char bufferB[2] = { 0x00, (char)(0xFF)};
    MoveWithOffset(bufferB, 0, bufferB + 1, 0, 1 * CHAR_BIT);
    EXPECT_EQ(bufferB[0], ((char)0xFF));
    EXPECT_EQ(bufferB[1], ((char)0xFF));
}

TEST_F(MoveWithBitOffset, SingleFullByteOffset)
{
    unsigned char bufferB[2] = { 0x00, (0xFF)};
    MoveWithOffset(bufferB, 0, bufferB + 1, 0, 1 * CHAR_BIT);
    EXPECT_EQ(0xFF, bufferB[0]);
    EXPECT_EQ(0xFF, bufferB[1]);
}

TEST_F(MoveWithBitOffset, TwoByteOffset)
{
    MoveWithOffset(bufferA, 0, bufferA + 2, 0, (kBufferASize - 2) * CHAR_BIT);
    EXPECT_EQ(checkBuffer[2], bufferA[0]);
    EXPECT_EQ(checkBuffer[3], bufferA[1]);
    EXPECT_EQ(checkBuffer[4], bufferA[2]);
    EXPECT_EQ(checkBuffer[5], bufferA[3]);
    EXPECT_EQ(checkBuffer[6], bufferA[4]);
    EXPECT_EQ(checkBuffer[7], bufferA[5]);
    EXPECT_EQ(checkBuffer[8], bufferA[6]);
    EXPECT_EQ(checkBuffer[9], bufferA[7]);
    // Untouched memory
    EXPECT_EQ(checkBuffer[8], bufferA[8]);
    EXPECT_EQ(checkBuffer[9], bufferA[9]);
}


TEST_F(MoveWithBitOffset, UnevenAlignedOffset)
{
    MoveWithOffset(bufferA, 2, bufferA + 2, 4, (kBufferASize - 2) * CHAR_BIT);
    EXPECT_EQ(checkBuffer[2], bufferA[0]);
    EXPECT_EQ(checkBuffer[3], bufferA[1]);
    EXPECT_EQ(checkBuffer[4], bufferA[2]);
    EXPECT_EQ(checkBuffer[5], bufferA[3]);
    EXPECT_EQ(checkBuffer[6], bufferA[4]);
    EXPECT_EQ(checkBuffer[7], bufferA[5]);
    EXPECT_EQ(checkBuffer[8], bufferA[6]);
    EXPECT_EQ(checkBuffer[9], bufferA[7]);
    // Untouched memory
    EXPECT_EQ(checkBuffer[8], bufferA[8]);
    EXPECT_EQ(checkBuffer[9], bufferA[9]);
}
