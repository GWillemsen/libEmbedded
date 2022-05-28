/**
 * @file Helpers.h
 * @author Giel Willemsen (g.willemsen@student.fontys.nl)
 * @brief Some helper functions that don't really have a place but are really handy.
 * @version 0.1
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
    template<typename T = int, typename TDivider = int>
    constexpr T DivdeByAndRoundUp(T value, TDivider divider)
    {
        T wholeValue = (value / divider);
        T partValue = (value - wholeValue) > 0 ? 1 : 0;
        return wholeValue + partValue;
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_HELPERS_H
