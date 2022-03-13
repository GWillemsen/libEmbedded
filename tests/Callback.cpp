#include <gtest/gtest.h>
#include "libEmbedded/Callback.h"
#include <vector>
#include <tuple>
#include <numeric>

using libEmbedded::Callback;

struct Context
{
    int hitCount;
    std::vector<std::tuple<int, short>> argValues;
};

typedef int callback_ret_type;
typedef callback_ret_type (*callback_with_type)(Context*, int, short);
typedef bool (*callback_check_type)(void*);

callback_ret_type CallbackImpl(Context *usrd, int i, short s)
{
    Context *context = (Context*)usrd;
    context->hitCount++;
    context->argValues.push_back(std::make_tuple(i, s));
    return true;
}


bool CallbackContextNullCheck(void *context)
{
    return context == nullptr;
}

TEST(CallbackTester, IsSetFromConstructor)
{
    Callback<callback_with_type, Context, callback_ret_type> cb(CallbackImpl, nullptr);
    ASSERT_TRUE(cb.IsSet());
}

TEST(CallbackTester, IsSetFromDefaultConstructor)
{
    Callback<callback_with_type, Context, callback_ret_type> cb;
    ASSERT_FALSE(cb.IsSet());
}

TEST(CallbackTester, CallbackSetAfterConstruction)
{
    Callback<callback_with_type, Context, callback_ret_type> cb;
    cb.SetCallback(CallbackImpl, nullptr);
    ASSERT_TRUE(cb.IsSet());
}

TEST(CallbackTester, CallbackCalledWithoutContext)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    cb.SetCallback(CallbackContextNullCheck, nullptr);
    ASSERT_TRUE(cb());
}

TEST(CallbackTester, CallbackCalledWithContext)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    cb.SetCallback(CallbackContextNullCheck, &cb);
    ASSERT_FALSE(cb());
}

TEST(CallbackTester, CallbackCalledWithoutCallback)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    ASSERT_FALSE(cb());
}

TEST(CallbackTester, CallbackInvokedWithoutContext)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    cb.SetCallback(CallbackContextNullCheck, nullptr);
    ASSERT_TRUE(cb.Invoke());
}

TEST(CallbackTester, CallbackInvokedWithContext)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    cb.SetCallback(CallbackContextNullCheck, &cb);
    ASSERT_FALSE(cb.Invoke());
}

TEST(CallbackTester, CallbackInvokedWithoutCallback)
{
    Callback<callback_check_type, void, callback_ret_type> cb;
    ASSERT_FALSE(cb.Invoke());
}

TEST(CallbackTester, CallbackInvokeCountCheck)
{
    Context hitContext = Context();
    Callback<callback_with_type, Context, callback_ret_type> cb(CallbackImpl, &hitContext);
    ASSERT_TRUE(cb.Invoke(std::numeric_limits<int>::max(), 10));
    ASSERT_EQ(1, hitContext.hitCount);
    ASSERT_EQ(1, hitContext.argValues.size());
    ASSERT_EQ(std::numeric_limits<int>::max(), std::get<0>(hitContext.argValues[0]));
    ASSERT_EQ(10, std::get<1>(hitContext.argValues[0]));
}
