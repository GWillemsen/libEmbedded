/**
 * @file Extracting.h
 * @author Giel Willemsen
 * @brief Some helper functions for extracting (sets of) bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.2 2022-10-30 Helper to extract values (ie, a set of bits as 1 value) from a larger value.
 * @version 0.3 2022-10-30 Variadic template argument simplification + added usage examples
 * @date 2022-10-30
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
         * Usage:
         * @code 
         * uint8_t a = ExtractBits(0xFA, 3, 5);
         * // a == 0x1F (5 bits starting at the 3rd bit)
         * @endcode
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
            return ((value & CreateMask(bitCount, startAtBit)) >> startAtBit) & CreateMask<T>(bitCount);
        }

        /**
         * @brief Extracts a value from a larger value.
         * 
         * Usage:
         * @code 
         * uint8_t a = 0;
         * ExtractValues(0xC0DE, a, 0, 8);
         * // a == 0xDE
         * @endcode
         * 
         * @tparam T The type of the value to extract bits from.
         * @tparam T2 The type to place the extracted bits in.
         * @param value The value to extract bits from.
         * @param part The value to put the extracted bits in.
         * @param startAt At what bit to start extracting.
         * @param bitCount The number of bits to extract.
         */
        template<typename T, typename T2 = T>
        void ExtractValues(T value, T2& part, size_t startAt, size_t bitCount)
        {
            part = ExtractBits(value, startAt, bitCount);
        }

        /**
         * @brief Extract a number of values from a larger value
         * The bits don't need to be aligned, extracting 11 bits starting at bit 3 is possible.
         * 
         * Usage:
         * @code 
         * uint8_t a = 0;
         * uint8_t b = 0;
         * ExtractValues(0xC0DE, a, 0, 8, b, 14, 2);
         * // a == 0xDE
         * // b == 0x3 (0xC>> 2)
         * @endcode
         * 
         * 
         * @tparam T The type of the value to extract bits from.
         * @tparam T2 The type to place the first group of extracted bits in.
         * @tparam T3 The type to place the second group of extracted bits in.
         * @tparam TOthers The types of the parameters for the other groups.
         * @param value The value to extract bits from.
         * @param part The value to put the first group of extracted bits in.
         * @param startAt At what bit to start extracting for the first value.
         * @param bitCount The number of bits to extract for the first value.
         * @param others Per 3 params: the part, startAt and bitCount for the next values to extract.
         */
        template<typename T, typename T2 = T, typename... TOthers>
        void ExtractValues(T value, T2& part, size_t startAt, size_t bitCount, TOthers&& ...others)
        {
            ExtractValues(value, part, startAt, bitCount);
            ExtractValues(value, others...);
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_EXTRACTION_H
