/**
 * @file Helpers.h
 * @author Giel Willemsen (g.willemsen@student.fontys.nl)
 * @brief Some helper functions that don't really have a place but are really handy.
 * @version 0.1 2022-05-22 Initial version
 * @version 0.2 2022-05-28 Cleanup and fixed negative rounding problem.
 * @date 2022-05-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_HELPERS_H
#define LIBEMBEDDED_HELPERS_H
#include "stdint.h"

namespace libEmbedded
{
    /**
     * @brief Divide the value by the divider and round the given value UP to closes T value.
     * Note: No floating point math required.
     * 
     * @tparam T The type of value that is divided.
     * @tparam TDivider The type of the value that is divided by.
     * @param value The value to divide.
     * @param divider The value to divide by.
     * @return T The quotient that is rounded up to closes value for T. 
     */
    template<typename T = int, typename TDivider = T, typename TResult = T>
    constexpr TResult DivideByAndRoundUp(T value, TDivider divider)
    {
        const TResult v = value;
        const TResult d = divider;
        const TResult wholeValue = (v / d);
        const TResult wholeValueD = wholeValue * d;
        const TResult leftOverValue = v - wholeValueD;
        TResult partValue = abs(leftOverValue) > 0 ? 1 : 0;
        if (((value < 0 && divider > 0) || (value > 0 && divider < 0)))
        {
            if (wholeValue <= 0)
            {
                partValue = 0;
            }
        }
        return wholeValue + partValue;
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_HELPERS_H
