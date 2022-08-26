#include <gtest/gtest.h>
#include "stdlib.h"
#include "libEmbedded/Expected.h"
#include "math.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

class Custom
{
private:
	int value;

public:
	static int copyConstructorCount;
	static int constructorCount;
	static int destructorCount;
	static int assignmentCount;

public:
	Custom(int val) : value(val)
	{
		constructorCount++;
	}

	Custom(const Custom &other) : value(other.value)
	{
		copyConstructorCount++;
	}

	Custom &operator=(const Custom &other)
	{
		this->value = value;
		assignmentCount++;
		return *this;
	}

	~Custom()
	{
		destructorCount++;
	}

	static void ResetCounters()
	{
		constructorCount = 0;
		copyConstructorCount = 0;
		destructorCount = 0;
		assignmentCount = 0;
	}

	int getValue()
	{
		return this->value;
	}
};

class ExpectedIntFloatFixture : public ::testing::Test
{
public:
	using Expected = libEmbedded::Expected<int, double>;
};

class ExpectedIntCustomFixture : public ::testing::Test
{
public:
	using Expected = libEmbedded::Expected<int, Custom>;
};

int Custom::copyConstructorCount = 0;
int Custom::constructorCount = 0;
int Custom::destructorCount = 0;
int Custom::assignmentCount = 0;

TEST_F(ExpectedIntFloatFixture, NormalExpected)
{
	const int a = 10;
	Expected exp = Expected::FromExpected(a);

	constexpr size_t kExpectedItemSize = MAX(sizeof(Expected::alternative), sizeof(Expected::expected));
	constexpr size_t kActualItemSize = Expected::kMaxItemSize;
	EXPECT_EQ(kActualItemSize, kExpectedItemSize);

	EXPECT_TRUE(exp.HasValue());
	EXPECT_TRUE(exp.HasExpected());
	EXPECT_EQ(a, exp.GetExpected());
}

TEST_F(ExpectedIntFloatFixture, AlternativeExpected)
{
	const double a = 10;
	Expected exp = Expected::FromAlternative(a);

	constexpr size_t kExpectedItemSize = MAX(sizeof(Expected::alternative), sizeof(Expected::expected));
	constexpr size_t kActualItemSize = Expected::kMaxItemSize;
	EXPECT_EQ(kActualItemSize, kExpectedItemSize);

	EXPECT_TRUE(exp.HasValue());
	EXPECT_FALSE(exp.HasExpected());
	EXPECT_FLOAT_EQ(a, exp.GetAlternative());
}

TEST_F(ExpectedIntCustomFixture, CopyConstructorAssignToSecondVariable)
{
	Custom::ResetCounters();
	{
		Custom custom(20);
		Expected a = Expected::FromAlternative(custom);
		Expected b = a;
		EXPECT_TRUE(b.HasValue());
		EXPECT_FALSE(b.HasExpected());
		custom.getValue();
	}

	EXPECT_EQ(1, Custom::constructorCount);
	EXPECT_EQ(2, Custom::copyConstructorCount);
	EXPECT_EQ(3, Custom::destructorCount);
	EXPECT_EQ(0, Custom::assignmentCount);
}

TEST_F(ExpectedIntCustomFixture, CopyConstructorAssignToSignleVariable)
{
	Custom::ResetCounters();
	{
		Custom custom(20);
		Expected a = Expected::FromAlternative(custom);
	}

	EXPECT_EQ(1, Custom::constructorCount);
	EXPECT_EQ(1, Custom::copyConstructorCount);
	EXPECT_EQ(2, Custom::destructorCount);
	EXPECT_EQ(0, Custom::assignmentCount);
}

TEST_F(ExpectedIntCustomFixture, CopyConstructorAssignAndAssignmentOperatorFromAToB)
{
	Custom::ResetCounters();
	{
		Custom custom(20);
		Expected a = Expected::FromAlternative(custom);
		Expected b = Expected::FromExpected(10);
		EXPECT_TRUE(a.HasValue());
		EXPECT_FALSE(a.HasExpected());

		EXPECT_TRUE(b.HasValue());
		EXPECT_TRUE(b.HasExpected());
		b = a;

		EXPECT_TRUE(b.HasValue());
		EXPECT_FALSE(b.HasExpected());
	}

	EXPECT_EQ(1, Custom::constructorCount);
	EXPECT_EQ(1, Custom::copyConstructorCount);
	EXPECT_EQ(1, Custom::assignmentCount);
	EXPECT_EQ(3, Custom::destructorCount);
}

TEST_F(ExpectedIntCustomFixture, CopyConstructorAssignAndAssignmentOperatorFromAlternative)
{
	Custom::ResetCounters();
	{
		Custom custom(20);
		Expected a = Expected::FromExpected(10);
		EXPECT_TRUE(a.HasValue());
		EXPECT_TRUE(a.HasExpected());

		a = Expected::FromAlternative(custom);

		EXPECT_TRUE(a.HasValue());
		EXPECT_FALSE(a.HasExpected());
	}

	EXPECT_EQ(1, Custom::constructorCount);
	EXPECT_EQ(1, Custom::copyConstructorCount);
	EXPECT_EQ(3, Custom::destructorCount);
	EXPECT_EQ(1, Custom::assignmentCount);
}

TEST_F(ExpectedIntFloatFixture, CopyConstructorAssignAndAssignmentOperatorFromAlternative)
{
	Expected a = Expected::FromExpected(10);
	EXPECT_TRUE(a.HasValue());
	EXPECT_TRUE(a.HasExpected());

	a = Expected::FromAlternative(20.0);

	EXPECT_TRUE(a.HasValue());
	EXPECT_FALSE(a.HasExpected());
}
