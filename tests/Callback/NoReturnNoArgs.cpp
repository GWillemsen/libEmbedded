#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include "CallbackHelper.h"
#include <atomic>

static int hitCount = 0;
static int withoutContextHits = 0;

using CallbackT = libEmbedded::Callback<CallbackNoReturnNoArgsType>;

static void CallbackWithoutInstanceContext(Context *context)
{
    hitCount++;
    if (context == nullptr)
    {
        withoutContextHits++;
    }
}

TEST(CallbackNoReturnNoArgs, InvokeWithoutContext)
{
    hitCount = 0;
    withoutContextHits = 0;
    CallbackT cb(CallbackWithoutInstanceContext, nullptr);
    cb.Invoke();
    ASSERT_EQ(1, hitCount);
    ASSERT_EQ(1, withoutContextHits);
}

TEST(CallbackNoReturnNoArgs, InvokeWithContext)
{
    Context context;
    CallbackT cb(CallbackFunctions<CallbackNoReturnNoArgsType>::DefaultFunction, &context);
    cb.Invoke();
    ASSERT_EQ(1, context.hitCount);
}

TEST(CallbackNoReturnNoArgs, InvokeWithContextButNoCallback)
{
    hitCount = 0;
    withoutContextHits = 0;
    Context context;
    CallbackT cb(CallbackT::CleanCallback, &context);
    cb.Invoke();
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
}
