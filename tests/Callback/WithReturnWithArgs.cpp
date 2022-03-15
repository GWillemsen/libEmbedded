#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include "CallbackHelper.h"

static int hitCount = 0;
static int withoutContextHits = 0;
static int lastArg = 0;

using libEmbedded::Callback;
using CallbackT = Callback<CallbackWithReturnWithArgsType>;
using Functions = CallbackFunctions<CallbackWithReturnWithArgsType>;
constexpr int kCallbackReturnValue = 404;

struct CustomTypeValue
{
public:
    static constexpr int kDefaultAB = 100;
    int ab;
    constexpr CustomTypeValue() : ab(kDefaultAB) {};
};

static int CallbackWithoutInstanceContext(Context *context, int arg)
{
    hitCount++;
    lastArg = arg;
    if (context == nullptr)
    {
        withoutContextHits++;
    }
    return kCallbackReturnValue;
}

TEST(CallbackWithReturnWithArgs, InvokeWithoutContext)
{
    constexpr int kArgument = 44;
    hitCount = 0;
    withoutContextHits = 0;
    CallbackT cb(CallbackWithoutInstanceContext, nullptr);
    ASSERT_EQ(kCallbackReturnValue, cb.Invoke(kArgument));
    ASSERT_EQ(1, hitCount);
    ASSERT_EQ(1, withoutContextHits);
    ASSERT_EQ(kArgument, lastArg);
}

TEST(CallbackWithReturnWithArgs, InvokeWithContext)
{
    constexpr int kArgument = 50;
    Context context;
    CallbackT cb(Functions::DefaultFunction, &context);
    ASSERT_EQ(Functions::kReturnOffset + 1, cb.Invoke(kArgument));
    ASSERT_EQ(1, context.hitCount);
    ASSERT_EQ(kArgument, context.lastArgument);
}

TEST(CallbackWithReturnWithArgs, InvokeWithContextButNoCallback)
{
    constexpr int kArgument = 12;
    hitCount = 0;
    withoutContextHits = 0;
    lastArg = 0;
    Context context;
    CallbackT cb(CallbackT::CleanCallback, &context);
    ASSERT_EQ(0, cb.Invoke(kArgument));
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, context.lastArgument);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
    ASSERT_EQ(0, lastArg);
}


TEST(CallbackWithReturnWithArgs, InvokeWithCustomTypeWithContextButNoCallback)
{
    typedef CustomTypeValue (*FPointer)(Context*, int);
    constexpr int kArgument = 13;
    hitCount = 0;
    withoutContextHits = 0;
    lastArg = 0;
    Context context;
    Callback<FPointer> cb(Callback<FPointer>::CleanCallback, &context);
    int abVal = CustomTypeValue::kDefaultAB;
    ASSERT_EQ(abVal, cb.Invoke(kArgument).ab);
    ASSERT_EQ(0, context.hitCount);
    ASSERT_EQ(0, context.lastArgument);
    ASSERT_EQ(0, hitCount);
    ASSERT_EQ(0, withoutContextHits);
    ASSERT_EQ(0, lastArg);
}
