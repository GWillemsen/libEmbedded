#include <limits.h>
#include <limits>
#include <numeric>
#include "gtest/gtest.h"
#include "libEmbedded/bits/Helpers.h"

using libEmbedded::bits::GetBitSize;

TEST(GetBitSizeTester, GetSizeOfChar)
{
    ASSERT_EQ(8, GetBitSize<char>());
    ASSERT_EQ(8, GetBitSize<signed char>());
    ASSERT_EQ(8, GetBitSize<unsigned char>());
}

TEST(GetBitSizeTester, GetSizeOfShort)
{
    ASSERT_EQ(16, GetBitSize<short>());
    ASSERT_EQ(16, GetBitSize<signed short>());
    ASSERT_EQ(16, GetBitSize<unsigned short>());
}

TEST(GetBitSizeTester, GetSizeOfInt)
{
    ASSERT_EQ(32, GetBitSize<int>());
    ASSERT_EQ(32, GetBitSize<signed int>());
    ASSERT_EQ(32, GetBitSize<unsigned int>());
}
