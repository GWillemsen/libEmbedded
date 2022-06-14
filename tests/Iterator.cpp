#include <gtest/gtest.h>
#include "libEmbedded/Iterator.h"
#include "libEmbedded/Span.h"
#include <array>
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

class FindIteratorFixture : public ::testing::Test
{
public:
    uint8_t data[kItemCount] = { 1,2,3,4,5,7,4,5,9};
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

TYPED_TEST(SpanIteratorFixture, RetrieveDistanceFromContainer)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    ASSERT_EQ(kItemCount, libEmbedded::Distance(list));
}

TYPED_TEST(SpanIteratorFixture, AdvanceBeginningToEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::iterator it = list.begin();
    libEmbedded::Advance(it, kItemCount);
    ASSERT_EQ(list.end(), it);
}

TYPED_TEST(SpanIteratorFixture, AdvanceDefaultN)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::iterator it = list.begin();
    const typename TypeParam::iterator kCheckTo = libEmbedded::Next(list.begin());
    libEmbedded::Advance(it);
    ASSERT_EQ(kCheckTo, it);
}

TYPED_TEST(SpanIteratorFixture, AdvanceBeginningToHalfWay)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::iterator it = list.begin();
    libEmbedded::Advance(it, kItemCount / 2);
    ASSERT_EQ(std::next(list.begin(), kItemCount / 2), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToNextFromBeginning)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Next(list.cbegin());;
    
    ASSERT_EQ(std::next(list.begin(), 1), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToSecondFromBeginning)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Next(list.cbegin(), 2);;
    
    ASSERT_EQ(std::next(list.cbegin(), 2), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToHalfFromBeginning)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Next(list.begin(), kItemCount / 2);;
    
    ASSERT_EQ(std::next(list.begin(), kItemCount / 2), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToEndFromBeginning)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Next(list.begin(), kItemCount);;
    
    ASSERT_EQ(list.end(), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToBeginningFromEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Prev(list.end(), kItemCount);;
    
    ASSERT_EQ(list.begin(), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToOneBeforeEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Prev(list.end());;
    
    ASSERT_EQ(std::prev(list.end()), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToTwoBeforeEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Prev(list.end(), 2);;
    
    ASSERT_EQ(std::prev(list.end(), 2), it);
}

TYPED_TEST(SpanIteratorFixture, MoveToHalfwayFromEnd)
{
    TypeParam list = Creators<TypeParam>::Create(this->data, this->data + kItemCount);
    typename TypeParam::const_iterator it = libEmbedded::Prev(list.end(), kItemCount / 2);;
    
    ASSERT_EQ(std::prev(list.end(), kItemCount / 2), it);
}


TEST_F(FindIteratorFixture, FindKeyThatIsInHaystack)
{
    uint8_t keyData[3] = { 3,4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 3);
    libEmbedded::Span<uint8_t> list = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(list.begin(), list.end(), key.begin(), key.end(), foundAt);
    ASSERT_TRUE(found);
    ASSERT_EQ(libEmbedded::Next(list.begin(), 2), foundAt);
}

TEST_F(FindIteratorFixture, FindKeyThatIsMultipleTimesInHaystack)
{
    uint8_t keyData[2] = { 4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_TRUE(found);
    ASSERT_EQ(libEmbedded::Next(haystack.begin(), 3), foundAt);
}

TEST_F(FindIteratorFixture, FindKeyThatIsMultipleTimesInHaystackButStartAtOffset)
{
    uint8_t keyData[2] = { 4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(libEmbedded::Next(haystack.begin(), 4), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_TRUE(found);
    ASSERT_EQ(libEmbedded::Next(haystack.begin(), 6), foundAt);
}

TEST_F(FindIteratorFixture, FindKeyThatIsNotInHaystack)
{
    uint8_t keyData[2] = { 4, 3};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_FALSE(found);
}

TEST_F(FindIteratorFixture, FindKeyThatPartialAtEndHaystack)
{
    uint8_t keyData[3] = { 5, 9, 10};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 3);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_FALSE(found);
}

TEST_F(FindIteratorFixture, FindEmptyKeyInHaystack)
{
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(nullptr, (size_t)0);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_FALSE(found);
}

TEST_F(FindIteratorFixture, FindKeyInEmptyHaystack)
{
    uint8_t keyData[2] = { 4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(nullptr, (size_t)0);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_FALSE(found);
}

TEST_F(FindIteratorFixture, FindEmptyKeyInEmptyHaystack)
{
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(nullptr, (size_t)0);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(nullptr, (size_t)0);
    libEmbedded::Span<uint8_t>::iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack.begin(), haystack.end(), key.begin(), key.end(), foundAt);
    ASSERT_FALSE(found);
}

TEST_F(FindIteratorFixture, FindKeyThatIsMultipleTimesInHaystack_ContainerShortcut)
{
    uint8_t keyData[2] = { 4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::const_iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack, key.cbegin(), key.cend(), foundAt);
    ASSERT_TRUE(found);
    ASSERT_EQ(libEmbedded::Next(haystack.begin(), 3), foundAt);
}

TEST_F(FindIteratorFixture, FindKeyThatIsMultipleTimesInHaystack_ContainerHayKeyShortcut)
{
    uint8_t keyData[2] = { 4,5};
    libEmbedded::Span<uint8_t> key = libEmbedded::Span<uint8_t>(keyData, keyData + 2);
    libEmbedded::Span<uint8_t> haystack = libEmbedded::Span<uint8_t>(this->data, this->data + kItemCount);
    libEmbedded::Span<uint8_t>::const_iterator foundAt;
    bool found = libEmbedded::FindStartOf(haystack, key, foundAt);
    ASSERT_TRUE(found);
    ASSERT_EQ(libEmbedded::Next(haystack.begin(), 3), foundAt);
}
