#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include "CallbackHelper.h"
#include <atomic>

static int hitCount = 0;
static int withoutContextHits = 0;
constexpr int kCallbackReturnValue = 404;

using libEmbedded::Callback;
using CallbackT = Callback<CallbackWithReturnNoArgsType>;

struct CustomTypeValue
{
public:
    static constexpr int kDefaultAB = 100;
    int ab;
    constexpr CustomTypeValue() : ab(kDefaultAB) {};
};

static int CallbackWithoutInstanceContext(Context *context)
{
    hitCount++;
    if (context == nullptr)
    {
        withoutContextHits++;
    }
    return kCallbackReturnValue;
}

TEST(CallbackWithReturnNoArgs, InvokeWithoutContext)
{
    hitCount = 0;
    withoutContextHits = 0;
    CallbackT cb(CallbackWithoutInstanceContext, nullptr);
    ASSERT_EQ(kCallbackReturnValue, cb.Invoke());
    ASSERT_EQ(1, hitCount);
    ASSERT_EQ(1, withoutContextHits);
}

TEST(CallbackWithReturnNoArgs, InvokeWithContext)
{
    Context context;
    CallbackT cb(CallbackFunctions<CallbackWithReturnNoArgsType>::DefaultFunction, &context);
    cb.Invoke();
    ASSERT_EQ(1, context.hitCount);
}


TEST(CallbackWithReturnNoArgs, InvokeWithContextButNoCallback)
{
    hitCount = 0;
    withoutContextHits = 0;
    Context context;
    CallbackT cb(CallbackT::CleanCallback, &context);
    ASSERT_EQ(0, cb.Invoke());
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, context.lastArgument);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
}

TEST(CallbackWithReturnNoArgs, InvokeWithCustomTypeWithContextButNoCallback)
{
    typedef CustomTypeValue (*FPointer)(Context*);
    hitCount = 0;
    withoutContextHits = 0;
    Context context;
    Callback<FPointer> cb(Callback<FPointer>::CleanCallback, &context);
    int abVal = CustomTypeValue::kDefaultAB;
    ASSERT_EQ(abVal, cb.Invoke().ab);
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, context.lastArgument);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
}

