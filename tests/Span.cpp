#include <gtest/gtest.h>
#include "libEmbedded/Span.h"
#include <limits.h>
#include <array>
#include <iterator>
#include <type_traits>

using libEmbedded::Span;
constexpr size_t kArraySize = 5;
class SpanFixture : public ::testing::Test
{
protected:
    using SpanT = Span<uint8_t, uint8_t*>;
    std::array<uint8_t, kArraySize> array {0, 1, 100, 90, UINT8_MAX};
};

template<typename T, typename K>
struct TemplateHelper
{
    using Type = T;
    using Span = K;
};

template<typename T>
class SpanTFixture : public ::testing::Test
{
protected:
    using SpanT = typename T::Span;
    std::array<typename T::Type, kArraySize> array {0, 1, 100, 90, UINT8_MAX};
};

using TestTypes = ::testing::Types<
    TemplateHelper<uint8_t, Span<uint8_t, uint8_t*, const uint8_t*>>,
    TemplateHelper<const uint8_t, Span<const uint8_t, const uint8_t*>>
>;

TYPED_TEST_SUITE(SpanTFixture, TestTypes);

TEST_F(SpanFixture, ConstructSpanFromStartAndLength)
{
    SpanT span(this->array.data(), kArraySize);

    ASSERT_EQ(this->array[0], *span.begin());
    ASSERT_EQ(this->array[kArraySize - 1], *(std::prev(span.end())));
}

TEST_F(SpanFixture, WriteToIterator)
{
    constexpr uint8_t kNewValue = 90;
    SpanT span(this->array.data(), kArraySize);

    SpanT::iterator it = span.begin();
    std::advance(it, 3);
    ASSERT_EQ(this->array[3], *it);
    *it = kNewValue;
    ASSERT_EQ(this->array[3], kNewValue);
}

TEST_F(SpanFixture, SpanStartEndIteratorOverRegularPP)
{
    SpanT span(this->array.data(), this->array.data() + kArraySize);
    SpanT::iterator it = span.begin();
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[0], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[2], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[3], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[4], *it);
    it++;
}

TEST_F(SpanFixture, SpanStartEndIteratorOverRegularPE)
{
    SpanT span(this->array.data(), this->array.data() + kArraySize);
    SpanT::iterator it = span.begin();
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[0], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[2], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[3], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[4], *it);
    it += 1;
}

TEST_F(SpanFixture, ReverseSpanStartEndIteratorOverRegularMM)
{
    SpanT span(this->array.data(), this->array.data() + kArraySize);
    SpanT::iterator it = span.end();
    ASSERT_NE(span.begin(), it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[4], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[3], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[2], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[1], *it);
    it--;
    ASSERT_EQ(span.begin(), it);
    EXPECT_EQ(this->array[0], *it);
}

TEST_F(SpanFixture, ReverseStartEndIteratorOverRegularME)
{
    SpanT span(this->array.data(), this->array.data() + kArraySize);
    SpanT::iterator it = span.end();
    ASSERT_NE(span.begin(), it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[4], *it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[3], *it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[2], *it);
    it -= 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it -= 1;
    ASSERT_EQ(span.begin(), it);
    EXPECT_EQ(this->array[0], *it);
}

TYPED_TEST(SpanTFixture, SpanStartEndConstSpanIteratorOverRegularPP)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.begin();
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[0], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[2], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[3], *it);
    it++;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[4], *it);
    it++;
}

TYPED_TEST(SpanTFixture, SpanStartEndConstSpanIteratorOverRegularPE)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.begin();
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[0], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[2], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[3], *it);
    it += 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[4], *it);
    it += 1;
}

TYPED_TEST(SpanTFixture, ReverseSpanStartEndConstSpanIteratorOverRegularMM)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.end();
    ASSERT_NE(span.begin(), it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[4], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[3], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[2], *it);
    it--;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[1], *it);
    it--;
    ASSERT_EQ(span.begin(), it);
    EXPECT_EQ(this->array[0], *it);
}

TYPED_TEST(SpanTFixture, ReverseStartEndConstSpanIteratorOverRegularME)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.end();
    ASSERT_NE(span.begin(), it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[4], *it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[3], *it);
    it -= 1;
    ASSERT_NE(span.begin(), it);
    EXPECT_EQ(this->array[2], *it);
    it -= 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it -= 1;
    ASSERT_EQ(span.begin(), it);
    EXPECT_EQ(this->array[0], *it);
}

TYPED_TEST(SpanTFixture, SpanStartEndConstCallIteratorOverRegularPP)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.cbegin();
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[0], *it);
    it++;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[1], *it);
    it++;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[2], *it);
    it++;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[3], *it);
    it++;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[4], *it);
    it++;
}

TYPED_TEST(SpanTFixture, SpanStartEndConstCallIteratorOverRegularPE)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.begin();
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[0], *it);
    it += 1;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[1], *it);
    it += 1;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[2], *it);
    it += 1;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[3], *it);
    it += 1;
    ASSERT_NE(span.cend(), it);
    EXPECT_EQ(this->array[4], *it);
    it += 1;
}

TYPED_TEST(SpanTFixture, ReverseSpanStartEndConstCallIteratorOverRegularMM)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.cend();
    ASSERT_NE(span.cbegin(), it);
    it--;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[4], *it);
    it--;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[3], *it);
    it--;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[2], *it);
    it--;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[1], *it);
    it--;
    ASSERT_EQ(span.cbegin(), it);
    EXPECT_EQ(this->array[0], *it);
}

TYPED_TEST(SpanTFixture, ReverseStartEndConstCallIteratorOverRegularME)
{
    const typename SpanTFixture<TypeParam>::SpanT span(this->array.data(), this->array.data() + kArraySize);
    typename SpanTFixture<TypeParam>::SpanT::const_iterator it = span.cend();
    ASSERT_NE(span.cbegin(), it);
    it -= 1;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[4], *it);
    it -= 1;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[3], *it);
    it -= 1;
    ASSERT_NE(span.cbegin(), it);
    EXPECT_EQ(this->array[2], *it);
    it -= 1;
    ASSERT_NE(span.end(), it);
    EXPECT_EQ(this->array[1], *it);
    it -= 1;
    ASSERT_EQ(span.cbegin(), it);
    EXPECT_EQ(this->array[0], *it);
}
