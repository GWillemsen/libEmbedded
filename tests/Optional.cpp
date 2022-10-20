#include <gtest/gtest.h>
#include "stdlib.h"
#include "libEmbedded/Optional.h"
#include "math.h"
#include "CustomHelper.h"
#include <thread>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct CustomCounter {
	static int copyConstructorCount;
	static int moveConstructorCount;
	static int constructorCount;
	static int destructorCount;
	static int assignmentCount;
	static int moveAssignmentCount;

	static void ResetCounters()
	{
		constructorCount = 0;
		copyConstructorCount = 0;
		moveConstructorCount = 0;
		destructorCount = 0;
		assignmentCount = 0;
        moveAssignmentCount = 0;
	}
};

int CustomCounter::copyConstructorCount = 0;
int CustomCounter::moveConstructorCount = 0;
int CustomCounter::constructorCount = 0;
int CustomCounter::destructorCount = 0;
int CustomCounter::assignmentCount = 0;
int CustomCounter::moveAssignmentCount = 0;

using Custom = CustomType<CustomCounter>;

class OptionalIntFixture : public ::testing::Test
{
public:
	using Optional = libEmbedded::Optional<int>;
};

class OptionalCustomFixture : public ::testing::Test
{
public:
	using Optional = libEmbedded::Optional<Custom>;
};

TEST_F(OptionalIntFixture, ConstructFromValue)
{
	constexpr int a = 10;
	Optional exp = Optional(a);

	EXPECT_TRUE(exp.IsSet());
	EXPECT_EQ(a, exp.Get());
}

TEST_F(OptionalIntFixture, ConstructEmpty)
{
	Optional exp = Optional();

	EXPECT_FALSE(exp.IsSet());
}

TEST_F(OptionalIntFixture, AssignEmptyFromT)
{
	constexpr int kValue = 20;
	Optional exp = Optional();

	EXPECT_FALSE(exp.IsSet());

	exp = kValue;

	EXPECT_TRUE(exp.IsSet());
	EXPECT_EQ(kValue, exp.Get());
}

TEST_F(OptionalIntFixture, AssignSetFromT)
{
	constexpr int kValue = 20;
	constexpr int kValueSecondary = 40;
	Optional exp = Optional(kValueSecondary);

	EXPECT_TRUE(exp.IsSet());
	EXPECT_EQ(kValueSecondary, exp.Get());

	exp = kValue;

	EXPECT_TRUE(exp.IsSet());
	EXPECT_EQ(kValue, exp.Get());
}

TEST_F(OptionalCustomFixture, CopyConstructorAssignToSecondVariable)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		Optional b = a;
		EXPECT_TRUE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
		custom.getValue();
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(2, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(3, CustomCounter::destructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
    EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
}

TEST_F(OptionalCustomFixture, ConstructFromExisting)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
        (void)a;
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(1, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(2, CustomCounter::destructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
    EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
}

TEST_F(OptionalCustomFixture, ConstructFromExistingAndAssignOptionalToNewEmptyVariable)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		Optional b;
		EXPECT_TRUE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
		b = a;

		EXPECT_TRUE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
        EXPECT_EQ(custom, a.Get());
        EXPECT_EQ(custom, b.Get());
        EXPECT_EQ(a.Get(), b.Get());
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(2, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(3, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, ConstructFromExistingAndAssignOptionalToNewSetVariable)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Custom customOther(30);
		Optional a = Optional(custom);
		Optional b = Optional(customOther);
		EXPECT_TRUE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
		b = a;

		EXPECT_TRUE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
        EXPECT_EQ(custom, a.Get());
        EXPECT_EQ(custom, b.Get());
        EXPECT_EQ(a.Get(), b.Get());
	}

	EXPECT_EQ(2, CustomCounter::constructorCount);
	EXPECT_EQ(2, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(1, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(4, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveConstructFromExisting)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		Optional b = Optional(std::move(a));
		EXPECT_FALSE(a.IsSet());
		EXPECT_TRUE(b.IsSet());

        EXPECT_EQ(custom, b.Get());
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(1, CustomCounter::copyConstructorCount);
	EXPECT_EQ(1, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(2, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignEmptyFromExisting)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		Optional b;
		EXPECT_TRUE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
        b = std::move(a);
		EXPECT_FALSE(a.IsSet());
		EXPECT_TRUE(b.IsSet());

        EXPECT_EQ(custom, b.Get());
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(1, CustomCounter::copyConstructorCount);
	EXPECT_EQ(1, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(2, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignSetFromExisting)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Custom customOther(40);
		Optional a = Optional(custom);
		Optional b = Optional(customOther);
		EXPECT_TRUE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
        b = std::move(a);
		EXPECT_FALSE(a.IsSet());
		EXPECT_TRUE(b.IsSet());

        EXPECT_EQ(custom, b.Get());
	}

	EXPECT_EQ(2, CustomCounter::constructorCount);
	EXPECT_EQ(2, CustomCounter::copyConstructorCount);
	EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(1, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(3, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, CopyConstructorEmptyAssignToSecondVariable)
{
	CustomCounter::ResetCounters();
	{
		Optional a;
		Optional b = a;
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
	}

	EXPECT_EQ(0, CustomCounter::constructorCount);
	EXPECT_EQ(0, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::destructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
    EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
}

TEST_F(OptionalCustomFixture, ConstructFromEmptyAndAssignOptionalToNewVariable)
{
	CustomCounter::ResetCounters();
	{
		Optional a = Optional();
		Optional b;
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
		b = a;

		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
	}

	EXPECT_EQ(0, CustomCounter::constructorCount);
	EXPECT_EQ(0, CustomCounter::copyConstructorCount);
    EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(0, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveConstructFromEmpty)
{
	CustomCounter::ResetCounters();
	{
		Optional a = Optional();
		Optional b = Optional(std::move(a));
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
	}

	EXPECT_EQ(0, CustomCounter::constructorCount);
	EXPECT_EQ(0, CustomCounter::copyConstructorCount);
	EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(0, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignEmptyFromEmpty)
{
	CustomCounter::ResetCounters();
	{
		Optional a = Optional();
		Optional b;
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
        b = std::move(a);
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
	}

	EXPECT_EQ(0, CustomCounter::constructorCount);
	EXPECT_EQ(0, CustomCounter::copyConstructorCount);
	EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(0, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignSetFromEmpty)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional();
		Optional b = Optional(custom);
		EXPECT_FALSE(a.IsSet());
		EXPECT_TRUE(b.IsSet());
        b = std::move(a);
		EXPECT_FALSE(a.IsSet());
		EXPECT_FALSE(b.IsSet());
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(1, CustomCounter::copyConstructorCount);
	EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(2, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignEmptyFromT)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional();
		EXPECT_FALSE(a.IsSet());
        a = std::move(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, a.Get().getValue());
	}

	EXPECT_EQ(1, CustomCounter::constructorCount);
	EXPECT_EQ(0, CustomCounter::copyConstructorCount);
	EXPECT_EQ(1, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(0, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(2, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, MoveAssignSetFromT)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Custom customOther(40);
		Optional a = Optional(customOther);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(40, a.Get().getValue());
		EXPECT_EQ(customOther, a.Get());
        a = std::move(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, a.Get().getValue());
		EXPECT_EQ(custom, a.Get());
	}

	EXPECT_EQ(2, CustomCounter::constructorCount);
	EXPECT_EQ(1, CustomCounter::copyConstructorCount);
	EXPECT_EQ(0, CustomCounter::moveConstructorCount);
	EXPECT_EQ(0, CustomCounter::assignmentCount);
	EXPECT_EQ(1, CustomCounter::moveAssignmentCount);
	EXPECT_EQ(3, CustomCounter::destructorCount);
}

TEST_F(OptionalCustomFixture, DereferenceFromNonConst)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, (*a).getValue());
	}
}

TEST_F(OptionalCustomFixture, DereferenceFromConst)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		const Optional a = Optional(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, (*a).getValue());
	}
}

TEST_F(OptionalCustomFixture, PointerMemberFromNonConst)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		Optional a = Optional(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, a->getValue());
	}
}

TEST_F(OptionalCustomFixture, PointerMemberFromConst)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		const Optional a = Optional(custom);
		EXPECT_TRUE(a.IsSet());
		EXPECT_EQ(20, a->getValue());
	}
}

TEST_F(OptionalCustomFixture, ContextBasedBoolConversion)
{
	CustomCounter::ResetCounters();
	{
		Custom custom(20);
		const Optional a = Optional(custom);
		EXPECT_TRUE(a);
	}
}

