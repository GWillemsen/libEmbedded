#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include "CallbackHelper.h"

using libEmbedded::Callback;

template<typename TCallback>
class CallbackCommonOperationTests : public ::testing::Test
{
protected:
};

using TestCallbackTypes = ::testing::Types<CallbackWithReturnNoArgsType, 
                                            CallbackWithReturnWithArgsType, 
                                            CallbackNoReturnNoArgsType, 
                                            CallbackNoReturnWithArgsType>;

TYPED_TEST_SUITE(CallbackCommonOperationTests, TestCallbackTypes);

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameFromFunction)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    ASSERT_TRUE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameFromCopyConstructor)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(cb);
    ASSERT_TRUE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameFromAssignmentOperator)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context);
    cb2 = cb;
    ASSERT_TRUE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameDifferentContextedButSameFunction)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::DefaultFunction, &context2);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameDifferentFunctionsButSameContex)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualToSameDifferentAll)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualFromAssignmentOperator)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    cb2 = cb;
    ASSERT_TRUE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpEqualFromDifferentWithAssignmentOperator)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(cb);
    Callback<TypeParam> cb3(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    cb2 = cb3;
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInequalToSameFromFunction)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    ASSERT_FALSE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInequalToSameFromCopyConstructor)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(cb);
    ASSERT_FALSE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInequalToSameDifferentContextedButSameFunction)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::DefaultFunction, &context2);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInequalToSameDifferentFunctionsButSameContex)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInEqualToSameDifferentAll)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInEqualFromAssignmentOperator)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    cb2 = cb;
    ASSERT_FALSE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, CmpInequalFromDifferentWithAssignmentOperator)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2(cb);
    Callback<TypeParam> cb3(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    cb2 = cb3;
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, IsSetOnEmpty)
{
    Callback<TypeParam> cb;
    ASSERT_FALSE(cb.IsSet());
}

TYPED_TEST(CallbackCommonOperationTests, IsSetAfterSettingAClearOne)
{
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, nullptr);
    cb.SetCallback(Callback<TypeParam>::CleanCallback, nullptr);
    ASSERT_FALSE(cb.IsSet());
}

TYPED_TEST(CallbackCommonOperationTests, EqualityCompareBetweenConstructorAndSetCallbackDifferentContexts)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::DefaultFunction, &context2);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, EqualityCompareBetweenConstructorAndSetCallbackDifferentCallbacks)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::OtherFunction, &context);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, EqualityCompareBetweenConstructorAndSetCallbackDifferentBoth)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    ASSERT_FALSE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, EqualityCompareBetweenConstructorAndSetCallbackWithSame)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    ASSERT_TRUE(cb == cb2);
}

TYPED_TEST(CallbackCommonOperationTests, InequalityCompareBetweenConstructorAndSetCallbackDifferentContexts)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::DefaultFunction, &context2);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, InequalityCompareBetweenConstructorAndSetCallbackDifferentCallbacks)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::OtherFunction, &context);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, InequalityCompareBetweenConstructorAndSetCallbackDifferentBoth)
{
    Context context;
    Context context2;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::OtherFunction, &context2);
    ASSERT_TRUE(cb != cb2);
}

TYPED_TEST(CallbackCommonOperationTests, InequalityCompareBetweenConstructorAndSetCallbackWithSame)
{
    Context context;
    Callback<TypeParam> cb(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    Callback<TypeParam> cb2;
    cb2.SetCallback(CallbackFunctions<TypeParam>::DefaultFunction, &context);
    ASSERT_FALSE(cb != cb2);
}
