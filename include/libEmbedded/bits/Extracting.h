/**
 * @file Extracting.h
 * @author Giel Willemsen
 * @brief Some helper functions for extracting (sets of) bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.2 2022-10-30 Helper to extract values (ie, a set of bits as 1 value) from a larger value.
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
         * @brief Extracts two values from a larger value.
         * 
         * @tparam T The type of the value to extract bits from.
         * @tparam T2 The type to place the first group of extracted bits in.
         * @tparam T3 The type to place the second group of extracted bits in.
         * @param value The value to extract bits from.
         * @param part The value to put the first group of extracted bits in.
         * @param startAt At what bit to start extracting for the first value.
         * @param bitCount The number of bits to extract for the first value.
         * @param part2 The value to put the second group of extracted bits in.
         * @param startAt2 At what bit to start extracting the second value.
         * @param bitCount2 The number of bits to extract for the second value.
         */
        template<typename T, typename T2 = T, typename T3 = T>
        void ExtractValues(T value, T2& part, size_t startAt, size_t bitCount, T3& part2, size_t startAt2, size_t bitCount2)
        {
            ExtractValues(value, part, startAt, bitCount);
            ExtractValues(value, part2, startAt2, bitCount2);
        }

        /**
         * @brief Extract a number of values from a larger value
         * 
         * @tparam T The type of the value to extract bits from.
         * @tparam T2 The type to place the first group of extracted bits in.
         * @tparam T3 The type to place the second group of extracted bits in.
         * @tparam TOthers The types of the parameters for the other groups.
         * @param value The value to extract bits from.
         * @param part The value to put the first group of extracted bits in.
         * @param startAt At what bit to start extracting for the first value.
         * @param bitCount The number of bits to extract for the first value.
         * @param part2 The value to put the second group of extracted bits in.
         * @param startAt2 At what bit to start extracting the second value.
         * @param bitCount2 The number of bits to extract for the second value.
         * @param others Per 3 params, the part, startAt and bitCount for the next values to extract.
         */
        template<typename T, typename T2 = T, typename T3 = T, typename... TOthers>
        void ExtractValues(T value, T2& part, size_t startAt, size_t bitCount, T3& part2, size_t startAt2, size_t bitCount2, TOthers&& ...others)
        {
            ExtractValues(value, part, startAt, bitCount);
            ExtractValues(value, part2, startAt2, bitCount2, others...);
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_EXTRACTION_H
