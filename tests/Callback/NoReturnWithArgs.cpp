#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include "CallbackHelper.h"

static int hitCount = 0;
static int withoutContextHits = 0;
static int lastArg = 0;

using CallbackT = libEmbedded::Callback<CallbackNoReturnWithArgsType>;

static void CallbackWithoutInstanceContext(Context *context, int arg)
{
    hitCount++;
    lastArg = arg;
    if (context == nullptr)
    {
        withoutContextHits++;
    }
}

TEST(CallbackNoReturnWithArgs, InvokeWithoutContext)
{
    constexpr int kArgument = 44;
    hitCount = 0;
    withoutContextHits = 0;
    CallbackT cb(CallbackWithoutInstanceContext, nullptr);
    cb.Invoke(kArgument);
    ASSERT_EQ(1, hitCount);
    ASSERT_EQ(1, withoutContextHits);
    ASSERT_EQ(kArgument, lastArg);
}

TEST(CallbackNoReturnWithArgs, InvokeWithContext)
{
    constexpr int kArgument = 50;
    Context context;
    CallbackT cb(CallbackFunctions<CallbackNoReturnWithArgsType>::DefaultFunction, &context);
    cb.Invoke(kArgument);
    ASSERT_EQ(1, context.hitCount);
    ASSERT_EQ(kArgument, context.lastArgument);
}

TEST(CallbackNoReturnWithArgs, InvokeWithContextButNoCallback)
{
    constexpr int kArgument = 12;
    hitCount = 0;
    withoutContextHits = 0;
    lastArg = 0;
    Context context;
    CallbackT cb(CallbackT::CleanCallback, &context);
    cb.Invoke(kArgument);
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, context.lastArgument);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
    ASSERT_EQ(0, lastArg);
}
