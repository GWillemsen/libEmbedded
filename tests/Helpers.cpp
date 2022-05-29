#include "gtest/gtest.h"
#include "libEmbedded/Helpers.h"
#include "limits.h"

using libEmbedded::DivideByAndRoundUp;

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
};

class DivideByAndRoundUpHelperFixture : public ::testing::TestWithParam<DivisionHelperStruct>
{};

TEST_P(DivideByAndRoundUpHelperFixture, ExactDivisionInt)
{
    int32_t kValue = GetParam().value;
    int8_t kDivider = GetParam().divider;
    int32_t result = DivideByAndRoundUp(kValue, kDivider);
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
    int32_t result = DivideByAndRoundUp(kValue, kDivider);
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
    double result = DivideByAndRoundUp<int16_t,int16_t,double>(kValue, kDivider);
    EXPECT_FLOAT_EQ(GetParam().flt_result, result);
}

TEST_P(DivideByAndRoundUpHelperFixture , RoundUpOnInputFloatsButResultInt)
{
    double kValue = GetParam().value;
    double kDivider = GetParam().divider;

    int16_t result = DivideByAndRoundUp<double,double, int16_t>(kValue, kDivider);
    EXPECT_EQ(GetParam().int_result, result);
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
