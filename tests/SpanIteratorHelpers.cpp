#include <gtest/gtest.h>
#include "libEmbedded/Span.h"
#include <list>

template<typename T>
struct Creators;

template<>
struct Creators<std::list<uint8_t>>
{
    template<typename It>
    static std::list<uint8_t> Create(It begin, It end)
    {
        return std::list<uint8_t>(begin, end);
    }
};

template<>
struct Creators<std::array<uint8_t, 9>>
{
    template<typename It>
    static std::array<uint8_t, 9> Create(It begin, It end)
    {
        auto arr = std::array<uint8_t, 9>();
        arr[0] = begin[0];
        arr[1] = begin[1];
        arr[2] = begin[2];
        arr[3] = begin[3];
        arr[4] = begin[4];
        arr[5] = begin[5];
        arr[6] = begin[6];
        arr[7] = begin[7];
        arr[8] = begin[8];
        return arr;
    }
};

template<>
struct Creators<libEmbedded::Span<uint8_t>>
{
    template<typename It>
    static libEmbedded::Span<uint8_t> Create(It begin, It end)
    {
        return libEmbedded::Span<uint8_t>(begin, end);
    }
};

constexpr size_t kItemCount = 9;
template<typename T>
class SpanIteratorFixture : public ::testing::Test
{
public:
    uint8_t data[kItemCount] = { 1,2,3,4,5,6,7,8,9};
};

using TestTypes = ::testing::Types<
    std::list<uint8_t>,
    std::array<uint8_t, 9>,
    libEmbedded::Span<uint8_t>
>;

TYPED_TEST_SUITE(SpanIteratorFixture, TestTypes);

TYPED_TEST(SpanIteratorFixture, RetrieveDistanceFromBeginToEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    ASSERT_EQ(kItemCount, libEmbedded::Distance(list.begin(), list.end()));
}

TYPED_TEST(SpanIteratorFixture, RetrieveDistanceFromBeginToEndMin5)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    ASSERT_EQ(kItemCount - 5, libEmbedded::Distance(list.begin(), std::prev(list.end(), 5)));
}

TYPED_TEST(SpanIteratorFixture, AdvanceBeginningToEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::iterator it = list.begin();
    libEmbedded::Advance(it, kItemCount);
    ASSERT_EQ(it, list.end());
}

TYPED_TEST(SpanIteratorFixture, AdvanceBeginningToHalfWay)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::iterator it = list.begin();
    libEmbedded::Advance(it, kItemCount / 2);
    ASSERT_EQ(it, std::next(list.begin(), kItemCount / 2));
}
