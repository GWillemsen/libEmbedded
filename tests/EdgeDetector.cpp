#include "gtest/gtest.h"
#include "libEmbedded/EdgeDetector.h"

using libEmbedded::EdgeType;
using ED = libEmbedded::EdgeDetector;

class EdgeDetectorConstructorFixture : public ::testing::TestWithParam<EdgeType>
{
protected:
};

class EdgeDetectorEqualityTesterFixture : public ::testing::TestWithParam<EdgeType>
{
protected:
};

class EdgeDetectorInEqualityTesterFixture : public ::testing::TestWithParam<EdgeType>
{
protected:
};

TEST_P(EdgeDetectorConstructorFixture, DefaultTrue)
{
    ED detector(GetParam(), true);
    ASSERT_TRUE(detector.GetState());
}

TEST_P(EdgeDetectorConstructorFixture, DefaultFalse)
{
    ED detector(GetParam(), false);
    ASSERT_FALSE(detector.GetState());
}

#pragma region "Detection after constructor"

#pragma region "Falling edge"

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartDefaultToFalse)
{
    ED detector(EdgeType::FALLING);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartDefaultToTrue)
{
    ED detector(EdgeType::FALLING);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartFalseToFalse)
{
    ED detector(EdgeType::FALLING, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartFalseToTrue)
{
    ED detector(EdgeType::FALLING, false);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartTrueToFalse)
{
    ED detector(EdgeType::FALLING, true);
    ASSERT_TRUE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(FallingEdgeDetectorEdgeAfterConstructor, StartTrueToTrue)
{
    ED detector(EdgeType::FALLING, true);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

#pragma endregion // Falling edge

#pragma region "Rising edge"

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartDefaultToFalse)
{
    ED detector(EdgeType::RISING);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartDefaultToTrue)
{
    ED detector(EdgeType::RISING);
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartFalseToFalse)
{
    ED detector(EdgeType::RISING, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartFalseToTrue)
{
    ED detector(EdgeType::RISING, false);
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartTrueToFalse)
{
    ED detector(EdgeType::RISING, true);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(RisingEdgeDetectorEdgeAfterConstructor, StartTrueToTrue)
{
    ED detector(EdgeType::RISING, true);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

#pragma endregion // Rising edge

#pragma region "Both edges"

TEST(BothEdgeDetectorEdgeAfterConstructor, StartDefaultToFalse)
{
    ED detector(EdgeType::BOTH);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(BothEdgeDetectorEdgeAfterConstructor, StartDefaultToTrue)
{
    ED detector(EdgeType::BOTH);
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(BothEdgeDetectorEdgeAfterConstructor, StartFalseToFalse)
{
    ED detector(EdgeType::RISING, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(BothEdgeDetectorEdgeAfterConstructor, StartFalseToTrue)
{
    ED detector(EdgeType::BOTH, false);
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

TEST(BothEdgeDetectorEdgeAfterConstructor, StartTrueToFalse)
{
    ED detector(EdgeType::BOTH, true);
    ASSERT_TRUE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(BothEdgeDetectorEdgeAfterConstructor, StartTrueToTrue)
{
    ED detector(EdgeType::BOTH, true);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_FALSE(detector.Update(true));
}

#pragma endregion // Both edges

#pragma endregion // Detection after constructor

#pragma region "Edges after initial updates"

#pragma region "Falling edge"

TEST(FallingEdgeDetectorInRuntime, StartFalse)
{
    ED detector(EdgeType::FALLING, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_TRUE(detector.Update(false));
}

TEST(FallingEdgeDetectorInRuntime, StartTrue)
{
    ED detector(EdgeType::FALLING, true);
    ASSERT_TRUE(detector.Update(false));
    ASSERT_FALSE(detector.Update(true));
    ASSERT_TRUE(detector.Update(false));
}

#pragma endregion // Falling edge

#pragma region "Rising edge"

TEST(RisingEdgeDetectorInRuntime, StartFalse)
{
    ED detector(EdgeType::RISING, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(RisingEdgeDetectorInRuntime, StartTrue)
{
    ED detector(EdgeType::RISING, true);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_TRUE(detector.Update(true));
    ASSERT_FALSE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

#pragma endregion // Rising edge

#pragma region "Both edges"

TEST(BothEdgeDetectorInRuntime, StartFalse)
{
    ED detector(EdgeType::BOTH, false);
    ASSERT_FALSE(detector.Update(false));
    ASSERT_TRUE(detector.Update(true));
    ASSERT_TRUE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

TEST(BothEdgeDetectorInRuntime, StartTrue)
{
    ED detector(EdgeType::BOTH, true);
    ASSERT_FALSE(detector.Update(true));
    ASSERT_TRUE(detector.Update(false));
    ASSERT_TRUE(detector.Update(true));
    ASSERT_TRUE(detector.Update(false));
    ASSERT_FALSE(detector.Update(false));
}

#pragma endregion // Both edges

#pragma endregion // Edges after initial updates

#pragma region "Equality operator"

TEST(EdgeDetectorEqualityTester, CompareFallingToRising)
{
    ED detector(EdgeType::FALLING);
    ED detector2(EdgeType::RISING);
    ASSERT_FALSE(detector == detector2);
    ASSERT_FALSE(detector2 == detector);
}

TEST(EdgeDetectorEqualityTester, CompareFallingToBoth)
{
    ED detector(EdgeType::FALLING);
    ED detector2(EdgeType::BOTH);
    ASSERT_FALSE(detector == detector2);
    ASSERT_FALSE(detector2 == detector);
}

TEST(EdgeDetectorEqualityTester, CompareRisingToBoth)
{
    ED detector(EdgeType::RISING);
    ED detector2(EdgeType::BOTH);
    ASSERT_FALSE(detector == detector2);
    ASSERT_FALSE(detector2 == detector);
}

TEST_P(EdgeDetectorEqualityTesterFixture, CopyConstructorEqual)
{
    ED detector(GetParam());
    ED detector2(detector);
    ASSERT_TRUE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, CopyConstructorEqualAfterUpdates)
{
    ED detector(GetParam());
    ED detector2(detector);
    detector.Update(true);
    detector2.Update(true);
    ASSERT_TRUE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, AssignmentOperatorEqual)
{
    ED detector(GetParam());
    ED detector2 = detector;
    ASSERT_TRUE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, AssignmentOperatorEqualAfterUpdates)
{
    ED detector(GetParam());
    ED detector2 = detector;
    detector.Update(true);
    detector2.Update(true);
    ASSERT_TRUE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, DifferentStartButSameEndState)
{
    ED detector(GetParam(), false);
    ED detector2(GetParam(), true);
    detector.Update(false);
    detector2.Update(false);
    ASSERT_TRUE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, DifferentStartAndDifferentEndState)
{
    ED detector(GetParam(), false);
    ED detector2(GetParam(), true);
    detector.Update(true);
    detector.Update(false);
    detector2.Update(false);
    detector2.Update(true);
    ASSERT_FALSE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, SameStartAndDifferentEndState)
{
    ED detector(GetParam(), true);
    ED detector2(GetParam(), true);
    detector.Update(true);
    detector.Update(false);
    detector2.Update(false);
    detector2.Update(true);
    ASSERT_FALSE(detector == detector2);
}

TEST_P(EdgeDetectorEqualityTesterFixture, SameStartAndSameEndState)
{
    ED detector(GetParam(), true);
    ED detector2(GetParam(), true);
    detector.Update(false);
    detector2.Update(false);
    ASSERT_TRUE(detector == detector2);
}

#pragma endregion // Equality operators

#pragma region "InEquality operators"

TEST(EdgeDetectorInEqualityTester, CompareFallingToRising)
{
    ED detector(EdgeType::FALLING);
    ED detector2(EdgeType::RISING);
    ASSERT_TRUE(detector != detector2);
    ASSERT_TRUE(detector2 != detector);
}

TEST(EdgeDetectorInEqualityTester, CompareFallingToBoth)
{
    ED detector(EdgeType::FALLING);
    ED detector2(EdgeType::BOTH);
    ASSERT_TRUE(detector != detector2);
    ASSERT_TRUE(detector2 != detector);
}

TEST(EdgeDetectorInEqualityTester, CompareRisingToBoth)
{
    ED detector(EdgeType::RISING);
    ED detector2(EdgeType::BOTH);
    ASSERT_TRUE(detector != detector2);
    ASSERT_TRUE(detector2 != detector);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, CopyConstructorEqual)
{
    ED detector(GetParam());
    ED detector2(detector);
    ASSERT_FALSE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, CopyConstructorEqualAfterUpdates)
{
    ED detector(GetParam());
    ED detector2(detector);
    detector.Update(true);
    detector2.Update(true);
    ASSERT_FALSE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, AssignmentOperatorEqual)
{
    ED detector(GetParam());
    ED detector2 = detector;
    ASSERT_FALSE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, AssignmentOperatorEqualAfterUpdates)
{
    ED detector(GetParam());
    ED detector2 = detector;
    detector.Update(true);
    detector2.Update(true);
    ASSERT_FALSE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, DifferentStartButSameEndState)
{
    ED detector(GetParam(), false);
    ED detector2(GetParam(), true);
    detector.Update(false);
    detector2.Update(false);
    ASSERT_FALSE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, DifferentStartAndDifferentEndState)
{
    ED detector(GetParam(), false);
    ED detector2(GetParam(), true);
    detector.Update(true);
    detector.Update(false);
    detector2.Update(false);
    detector2.Update(true);
    ASSERT_TRUE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, SameStartAndDifferentEndState)
{
    ED detector(GetParam(), true);
    ED detector2(GetParam(), true);
    detector.Update(true);
    detector.Update(false);
    detector2.Update(false);
    detector2.Update(true);
    ASSERT_TRUE(detector != detector2);
}

TEST_P(EdgeDetectorInEqualityTesterFixture, SameStartAndSameEndState)
{
    ED detector(GetParam(), true);
    ED detector2(GetParam(), true);
    detector.Update(false);
    detector2.Update(false);
    ASSERT_FALSE(detector != detector2);
}

#pragma endregion // InEquality operators


INSTANTIATE_TEST_SUITE_P(
    EdgeDetector, 
    EdgeDetectorConstructorFixture,
    ::testing::Values(
        EdgeType::BOTH, EdgeType::FALLING, EdgeType::RISING
    )
);

INSTANTIATE_TEST_SUITE_P(
    EdgeDetector, 
    EdgeDetectorEqualityTesterFixture,
    ::testing::Values(
        EdgeType::BOTH, EdgeType::FALLING, EdgeType::RISING
    )
);

INSTANTIATE_TEST_SUITE_P(
    EdgeDetector, 
    EdgeDetectorInEqualityTesterFixture,
    ::testing::Values(
        EdgeType::BOTH, EdgeType::FALLING, EdgeType::RISING
    )
);
