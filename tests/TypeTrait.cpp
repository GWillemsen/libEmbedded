#include "gtest/gtest.h"
#include "libEmbedded/TypeTrait.h"

using namespace libEmbedded;
using ::testing::StaticAssertTypeEq;

// Some sanity checks, not exhaustive, but to get a idea if it is working.
// This is just a small selection, based on what I recently used.

TEST(TypeTrait, remove_const)
{
    StaticAssertTypeEq<remove_const<uint8_t*>::type, uint8_t*>();
    StaticAssertTypeEq<remove_const<uint8_t* const>::type, uint8_t*>();
    StaticAssertTypeEq<remove_const<const uint8_t* const>::type, const uint8_t*>();
    StaticAssertTypeEq<remove_const<const uint8_t*>::type, const uint8_t*>();
    StaticAssertTypeEq<remove_const<const volatile uint8_t*>::type, const volatile uint8_t*>();
}
TEST(TypeTrait, remove_volatile)
{
    StaticAssertTypeEq<remove_volatile<uint8_t*>::type, uint8_t*>();
    StaticAssertTypeEq<remove_volatile<uint8_t* volatile>::type, uint8_t*>();
    StaticAssertTypeEq<remove_volatile<volatile uint8_t* volatile>::type, volatile uint8_t*>();
    StaticAssertTypeEq<remove_volatile<volatile uint8_t*>::type, volatile uint8_t*>();
    StaticAssertTypeEq<remove_volatile<volatile const uint8_t*>::type, volatile const uint8_t*>();
}

TEST(TypeTrait, remove_cv)
{
    StaticAssertTypeEq<remove_cv<uint8_t*>::type, uint8_t*>();
    StaticAssertTypeEq<remove_cv<const volatile uint8_t*>::type, const volatile uint8_t*>();
    StaticAssertTypeEq<remove_cv<const uint8_t* const volatile>::type, const uint8_t*>();
}

TEST(TypeTrait, remove_pointer)
{
    StaticAssertTypeEq<remove_pointer<uint8_t*>::type, uint8_t>();
    StaticAssertTypeEq<remove_pointer<const uint8_t*>::type, const uint8_t>();
    StaticAssertTypeEq<remove_pointer<uint8_t*&>::type, uint8_t*&>();
}

TEST(TypeTrait, remove_reference)
{
    StaticAssertTypeEq<remove_reference<uint8_t&>::type, uint8_t>();
    StaticAssertTypeEq<remove_reference<const uint8_t&>::type, const uint8_t>();
    StaticAssertTypeEq<remove_reference<uint8_t*&>::type, uint8_t*>();
}

TEST(TypeTrait, add_const)
{
    StaticAssertTypeEq<add_const<uint8_t*>::type, uint8_t* const>();
    StaticAssertTypeEq<add_const<uint8_t>::type, uint8_t const>();
    StaticAssertTypeEq<add_const<uint8_t>::type, const uint8_t>();
    StaticAssertTypeEq<add_const<uint8_t&>::type, uint8_t&>();
}

TEST(TypeTrait, add_volatile)
{
    StaticAssertTypeEq<add_volatile<uint8_t*>::type, uint8_t* volatile>();
    StaticAssertTypeEq<add_volatile<uint8_t>::type, uint8_t volatile>();
    StaticAssertTypeEq<add_volatile<uint8_t>::type, volatile uint8_t>();
    StaticAssertTypeEq<add_volatile<uint8_t&>::type, uint8_t&>();
}

TEST(TypeTrait, add_const_volatile)
{
    StaticAssertTypeEq<add_cv<uint8_t*>::type, uint8_t* const volatile>();
    StaticAssertTypeEq<add_cv<uint8_t>::type, uint8_t const volatile>();
    StaticAssertTypeEq<add_cv<uint8_t>::type, const volatile uint8_t>();
    StaticAssertTypeEq<add_cv<uint8_t&>::type, uint8_t&>();
}

TEST(TypeTrait, is_const)
{
    static_assert(is_const<uint8_t*>::value == false, "Failed.");
    static_assert(is_const<const uint8_t>::value, "Failed.");
    static_assert(is_const<uint8_t* const>::value, "Failed.");
    static_assert(is_const<const uint8_t&>::value == false, "Failed.");
    static_assert(is_const<const uint8_t* const>::value, "Failed.");
}

TEST(TypeTrait, is_volatile)
{
    static_assert(is_volatile<uint8_t*>::value == false, "Failed.");
    static_assert(is_volatile<volatile uint8_t>::value, "Failed.");
    static_assert(is_volatile<uint8_t* volatile>::value, "Failed.");
    static_assert(is_volatile<volatile uint8_t&>::value == false, "Failed.");
    static_assert(is_volatile<volatile uint8_t* volatile>::value, "Failed.");
}

TEST(TypeTrait, is_pointer)
{
    static_assert(is_pointer<uint8_t>::value == false, "Failed.");
    static_assert(is_pointer<uint8_t*>::value, "Failed.");
    static_assert(is_pointer<uint8_t&>::value == false, "Failed.");
    static_assert(is_pointer<const uint8_t*>::value, "Failed.");
    static_assert(is_pointer<const uint8_t* const>::value, "Failed.");
    static_assert(is_pointer<const uint8_t&>::value == false, "Failed.");
}

TEST(TypeTrait, is_reference)
{
    static_assert(is_reference<uint8_t>::value == false, "Failed.");
    static_assert(is_reference<uint8_t*>::value == false, "Failed.");
    static_assert(is_reference<uint8_t&>::value, "Failed.");
    static_assert(is_reference<const uint8_t&>::value, "Failed.");
    static_assert(is_reference<const uint8_t*>::value == false, "Failed.");
}
