/**
 * @file Helpers.h
 * @author Giel Willemsen
 * @brief Some helper functions that don't really have a place but are really handy.
 * @version 0.1 2022-05-22 Initial version
 * @version 0.2 2022-05-28 Cleanup and fixed negative rounding problem.
 * @version 0.3 2022-05-29 Removed dependency on math.h abs function.
 * @version 0.4 2022-10-30 DivideAndRoundUp is now a single statement (C++11 conformity).
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_HELPERS_H
#define LIBEMBEDDED_HELPERS_H
#include "stdint.h"
#include "libEmbedded/TypeTrait.h"

namespace libEmbedded
{
    /**
     * @brief Divide the value by the divider and round the given value UP to closes T value.
     * Note: No floating point math required.
     * 
     * @tparam T The type of value that is divided.
     * @tparam TResult The type of the quotient.
     * @param value The value to divide.
     * @param divider The value to divide by.
     * @return T The quotient that is rounded up to closes value for T. 
     */
    template<typename T = int, typename TResult = T>
    TResult DivideByAndRoundUp(T value, T divider)
    {
        return 
            (TResult)((TResult)value / divider) + // Whole
            (value != ((TResult)((TResult)value / divider) * divider) ? 
                // If the result is negative and one of the params is negative too
                // (This also implies the result is negative, but in case the TResult
                // type can represent negative numbers we still have to check of it,
                // but we can't only check that because we don't know if it was 0 then)
                ((((value < 0 && divider > 0) || (value > 0 && divider < 0)) && (((TResult)value / divider) <= 0)) ? 0 : 1)
                : 0
            );
    }

    /**
     * @brief Clamps the value of the given input at the min and max provided (min <= result <= max).
     * 
     * @tparam T The type of the data value to perform the clamp on.
     * @param input The input value to range clamp.
     * @param max The maximum result value.
     * @param min The minimum result value.
     * @return T The value of input never over the max, or below the min, provided.
     */
    template<typename T>
    constexpr T RangeClamp(const T& input, const T& max, const T& min)
    {
        return (input > max) ? max : ((input < min) ? min : input);
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_HELPERS_H
