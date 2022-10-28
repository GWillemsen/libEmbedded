#include <limits.h>
#include <limits>
#include <numeric>
#include "gtest/gtest.h"
#include "libEmbedded/bits/Util.h"

using libEmbedded::bits::GetBitSize;

TEST(GetBitSizeTester, GetSizeOfInt8)
{
    ASSERT_EQ(8, GetBitSize<int8_t>());
    ASSERT_EQ(8, GetBitSize<uint8_t>());
}

TEST(GetBitSizeTester, GetSizeOfInt16)
{
    ASSERT_EQ(16, GetBitSize<int16_t>());
    ASSERT_EQ(16, GetBitSize<uint16_t>());
}

TEST(GetBitSizeTester, GetSizeOfInt32)
{
    ASSERT_EQ(32, GetBitSize<int32_t>());
    ASSERT_EQ(32, GetBitSize<uint32_t>());
}
