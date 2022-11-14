#include "gtest/gtest.h"
#include "libEmbedded/Helpers.h"
#include "limits.h"

using libEmbedded::DivideByAndRoundUp;
using libEmbedded::RangeClamp;

struct DivisionHelperStruct
{
    int32_t value;
    int32_t divider;
    double flt_result;
    int32_t int_result;

    DivisionHelperStruct(int32_t value, int32_t divider, double flt_result, int32_t int_result) : 
        value(value), divider(divider), flt_result(flt_result), int_result(int_result)
    {
    }
    friend std::ostream & operator << (std::ostream &out, const DivisionHelperStruct &c);
};

std::ostream & operator << (std::ostream &out, const DivisionHelperStruct &c)
{
    out << "{" << c.value << "/" << c.divider << ":" << c.flt_result << ";" << c.int_result << "}";
    return out;
}

class DivideByAndRoundUpHelperFixture : public ::testing::TestWithParam<DivisionHelperStruct>
{};

class RangeClampInputHelperFixture : public ::testing::Test
{
public:
    const int kMax = 30;
    const int kMin = 5;
};

class RangeClampInputBelowMinHelperFixture : public RangeClampInputHelperFixture, public ::testing::WithParamInterface<int>
{};
class RangeClampInputAboveMaxHelperFixture : public RangeClampInputHelperFixture, public ::testing::WithParamInterface<int>
{};
class RangeClampInputInRangeHelperFixture : public RangeClampInputHelperFixture, public ::testing::WithParamInterface<int>
{};

TEST_P(DivideByAndRoundUpHelperFixture, ExactDivisionInt)
{
    int32_t kValue = GetParam().value;
    int8_t kDivider = GetParam().divider;
    int32_t result = DivideByAndRoundUp<int32_t>(kValue, kDivider);
    EXPECT_EQ(GetParam().int_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture, ExactDivisionFlt)
{
    double kValue = GetParam().value;
    double kDivider = GetParam().divider;
    double result = DivideByAndRoundUp(kValue, kDivider);
    EXPECT_FLOAT_EQ(GetParam().flt_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture, RoundUpOnInteger)
{
    int32_t kValue = GetParam().value;
    int8_t kDivider = GetParam().divider;
    int32_t result = DivideByAndRoundUp<int32_t>(kValue, kDivider);
    EXPECT_EQ(GetParam().int_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture , RoundUpOnFloat)
{
    double kValue = GetParam().value;
    double kDivider = GetParam().divider;
    double result = DivideByAndRoundUp(kValue, kDivider);
    EXPECT_FLOAT_EQ(GetParam().flt_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture , RoundUpOnInputIntsButResultFloat)
{
    int16_t kValue = GetParam().value;
    int16_t kDivider = GetParam().divider;
    double result = DivideByAndRoundUp<int16_t,double>(kValue, kDivider);
    EXPECT_FLOAT_EQ(GetParam().flt_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture , RoundUpOnInputFloatsButResultInt)
{
    double kValue = GetParam().value;
    double kDivider = GetParam().divider;

    int16_t result = DivideByAndRoundUp<double, int16_t>(kValue, kDivider);
    EXPECT_EQ(GetParam().int_result, result);
}

TEST_P(RangeClampInputInRangeHelperFixture, InputWithinRange)
{
    const int kExpected = GetParam();
    const int kInput = GetParam();
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

TEST_P(RangeClampInputAboveMaxHelperFixture, InputAboveRange)
{
    const int kInput = GetParam();
    const int kExpected = kMax;
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

TEST_P(RangeClampInputBelowMinHelperFixture, InputBelowRange)
{
    const int kExpected = kMin;
    const int kInput = GetParam();
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

TEST_F(RangeClampInputHelperFixture, InputEqualMaxRange)
{
    const int kExpected = kMax;
    const int kInput = kMax;
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

TEST_F(RangeClampInputHelperFixture, InputEqualMinRange)
{
    const int kExpected = kMin;
    const int kInput = kMin;
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

TEST_F(RangeClampInputHelperFixture, InputDoubleOnEdge)
{
    const int kExpected = 5;
    const int kInput = -500;
    const int kResult = RangeClamp(kInput, kMax, kMin);
    EXPECT_EQ(kExpected, kResult);
}

INSTANTIATE_TEST_SUITE_P(DivideByAndRoundUpHelper, DivideByAndRoundUpHelperFixture, testing::Values(
     DivisionHelperStruct(301,   3,     100.333333, 101)
    ,DivisionHelperStruct(300,  3,      100.0,      100)
    ,DivisionHelperStruct(10,   4,      2.5,        3)
    ,DivisionHelperStruct(12,   4,      3,          3)
    ,DivisionHelperStruct(-10,  100,    -0.1,       0)
    ,DivisionHelperStruct(-10,  -100,   0.1,        1)
    ,DivisionHelperStruct(-200, 100,    -2,         -2)
    ,DivisionHelperStruct(-200, -100,   2,          2)
    ,DivisionHelperStruct(-250, 100,    -2.5,       -2)
));

INSTANTIATE_TEST_SUITE_P(
    RangeClampInputBelowHelpers,
    RangeClampInputBelowMinHelperFixture,
    ::testing::Values(
        1, -10, 4, -100, -5000
));
INSTANTIATE_TEST_SUITE_P(
    RangeClampInputAboveHelpers,
    RangeClampInputAboveMaxHelperFixture,
    ::testing::Values(
        31, 35, 40, 100, 5000
));
INSTANTIATE_TEST_SUITE_P(
    RangeClampInputInRangeHelpers,
    RangeClampInputInRangeHelperFixture,
    ::testing::Values(
        5, 10, 15, 25, 30
));
