/**
 * @file Extracting.h
 * @author Giel Willemsen
 * @brief Some helper functions for extracting (sets of) bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_EXTRACTION_H
#define LIBEMBEDDED_BITS_EXTRACTION_H
#include <stddef.h>
#include "libEmbedded/bits/Masking.h"

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Extract bitCount bits starting at startAtBit. For every bit outside of the value of T a 0 is taken.
         * 
         * @tparam T The type of the value to extra from and the return value type.
         * @param value The value to extract bits from.
         * @param startAtBit At what bit to start extracting.
         * @param bitCount The number of bits to extract.
         * @return T The extracted bits.
         */
        template<typename T>
        constexpr T ExtractBits(T value, size_t startAtBit, size_t bitCount)
        {
            return (value >> startAtBit) & CreateMask<T>(bitCount);
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_EXTRACTION_H
