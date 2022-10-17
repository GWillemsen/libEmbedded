/**
 * @file CallbackHelper.h
 * @author Giel Willemsen
 * @brief Some 'sneaky' template specializations to allow parametrization for Typed Tests in Google test.
 * 
 * @version 0.1 2022-03-15 Initial version
 * @version 0.2 2022-10-17 Patched so that MSVC also passes the tests
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 * @details Because google tests and value parameterized tests don't seem to like each other much in Google Test
 * an alternative method is needed. Using template specialization some parameters for each type can be defined.
 * It also allows to specify specific parameters for a special type if needed.
 * Because the whole struct is specialized it is also possible to create specific methods for each type (and in case
 * of function pointers make them also private so they can't be used externally).
 * 
 */

#pragma once
#ifndef CALLBACK_HELPER
#define CALLBACK_HELPER

struct Context
{
    int hitCount;
    int lastArgument;
    constexpr Context() : hitCount(0), lastArgument(0) {}
};

typedef void (*CallbackNoReturnNoArgsType)(Context*);
typedef void (*CallbackNoReturnWithArgsType)(Context*, int a);
typedef int (*CallbackWithReturnNoArgsType)(Context*);
typedef int (*CallbackWithReturnWithArgsType)(Context*, int a);


template<typename TCallback> struct CallbackFunctions;

template<>
struct CallbackFunctions<CallbackWithReturnNoArgsType>
{
public:
    static constexpr int kReturnOffset = 300;
private:
    static int CallbackWithReturnNoArgs(Context *context)
    {
        context->hitCount++;
        return context->hitCount + kReturnOffset;
    }

    static int CallbackWithReturnNoArgsButDifferent(Context *context)
    {
        static volatile int counter = 0; // We need a difference with the default otherwise optimization creeps in.
        counter++;
        context->hitCount++;
        return context->hitCount + kReturnOffset;
    }
public:
    static constexpr CallbackWithReturnNoArgsType DefaultFunction = CallbackWithReturnNoArgs;
    static constexpr CallbackWithReturnNoArgsType OtherFunction = CallbackWithReturnNoArgsButDifferent;
};

template<>
struct CallbackFunctions<CallbackWithReturnWithArgsType>
{
public:
    static constexpr int kReturnOffset = 300;
private:
    static int CallbackWithReturnWithArgs(Context *context, int val)
    {
        context->hitCount++;
        context->lastArgument = val;
        return context->hitCount + kReturnOffset;
    }
    static int CallbackWithReturnWithArgsButDifferent(Context *context, int val)
    {
        context->hitCount++;
        context->lastArgument = val;
        static volatile int counter = 0; // We need a difference with the default otherwise optimization creeps in.
        counter++;
        return context->hitCount + kReturnOffset;
    }
public:
    static constexpr CallbackWithReturnWithArgsType DefaultFunction = CallbackWithReturnWithArgs;
    static constexpr CallbackWithReturnWithArgsType OtherFunction = CallbackWithReturnWithArgsButDifferent;
};

template<>
struct CallbackFunctions<CallbackNoReturnNoArgsType>
{
private:
    static void CallbackNoReturnNoArgs(Context *context)
    {
        context->hitCount++;
    }

    static void CallbackNoReturnNoArgsButDifferentName(Context *context)
    {
        static volatile int counter = 0; // We need a difference with the default otherwise optimization creeps in.
        counter++;
        context->hitCount++;
    }
public:
    static constexpr CallbackNoReturnNoArgsType DefaultFunction = CallbackNoReturnNoArgs;
    static constexpr CallbackNoReturnNoArgsType OtherFunction = CallbackNoReturnNoArgsButDifferentName;
};

template<>
struct CallbackFunctions<CallbackNoReturnWithArgsType>
{
private:
    static void CallbackNoReturnWithArgs(Context *context, int val)
    {
        context->hitCount++;
        context->lastArgument = val;
    }
    static void CallbackNoReturnWithArgsButDifferent(Context *context, int val)
    {
        static volatile int counter = 0; // We need a difference with the default otherwise optimization creeps in.
        counter++;
        context->hitCount++;
        context->lastArgument = val;
    }

public:
    static constexpr CallbackNoReturnWithArgsType DefaultFunction = CallbackNoReturnWithArgs;
    static constexpr CallbackNoReturnWithArgsType OtherFunction = CallbackNoReturnWithArgsButDifferent;
};

#endif // CALLBACK_HELPER
