/**
 * @file Combining.h
 * @author Giel Willemsen
 * @brief Some helper functions for combing (sets of) bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.1 2022-10-30 Added missing header + drop redundant GetCombinedValue (replaced by more versatile SetBits)
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_HELPERS_H
#define LIBEMBEDDED_BITS_HELPERS_H
#include <stddef.h>
#include <stdint.h>

#include "libEmbedded/bits/Masking.h"
#include "libEmbedded/bits/Extracting.h"
#include "libEmbedded/bits/Util.h"

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Take the two given values, extract the bits and paste them into the final value.
         * None of the inputs have checks so if you extract bits from outside the value (ex. extract
         * 8 bits of data starting at bit 16 on a 8 bit data type) then just 0's will be extracted.
         * 
         * @tparam T1 The type of the first value.
         * @tparam T2 The type of the second value.
         * @tparam T3 The return value type (decides how many bits can be returned!)
         * @param value1 The first value to extra bits from.
         * @param value2 The second value to extra bits from.
         * @param offsetValue1 At what bit to start extracting bits from in value 1.
         * @param bitsFrom1 How many bits extract from value 1.
         * @param offsetValue2 At what bit to start extracting bits from in value 2.
         * @param bitsFrom2 How many bits extract from value 1.
         * @return constexpr T3 The extract bits combined as 1 value.
         */
        template<typename T1, typename T2, typename T3>
        constexpr T3 CombineBitValues(T1 value1, T2 value2, size_t offsetValue1, size_t bitsFrom1, size_t offsetValue2, size_t bitsFrom2)
        {
            const T3 kValueFrom1 = (value1 >> offsetValue1) & CreateMask(bitsFrom1);
            const T3 kValueFrom2 = (value2 >> offsetValue2) & CreateMask(bitsFrom2);
            return ExtractBits(value1, offsetValue1, bitsFrom1) | (ExtractBits(value2, offsetValue2, bitsFrom2) << bitsFrom1);
        }


        /**
         * @brief Set the given value at the start position for length bits in the startValue.
         * 
         * @tparam T1 THe type of value to extract bits from.
         * @tparam T2 The type of the resulting value;
         * @param startValue The initial value to start out with.
         * @param value The value to extract bits from.
         * @param start The position in startValue to start inserting the bits from value.
         * @param length The number of bits to extract from value.
         * @return constexpr T2 The startValue but then with the new bits overwritten.
         */
        template<typename T1, typename T2>
        constexpr T2 SetBits(T2 startValue, T1 value, size_t start, size_t length)
        {
            return (startValue & ~CreateMask<T2>(length, start)) | ((T2)(value & CreateMask<T1>(length)) << start);
        }

        /**
         * @brief Set the given value at the start position for length bits in the startValue.
         * 
         * NOTE: The bits are set from right to left (so value2 is set before value, and value3 before value2)!
         * 
         * NOTE: Params must be given in multiples of 3 (value, start and length).
         * 
         * @tparam T1 The type of value to extract bits from.
         * @tparam T2 The type of the resulting value;
         * @tparam TOthers The type of the other params.
         * @param startValue The initial value to start out with.
         * @param value The value to extract bits from.
         * @param start The position in startValue to start inserting the bits from value.
         * @param length The number of bits to extract from value.
         * @param value2 The value to extract bits from.
         * @param start2 The position in startValue to start inserting the bits from value.
         * @param length2 The number of bits to extract from the second value.
         * @param n The other sets of value, start and length.
         * @return constexpr T2 The startValue but then with the new bits overwritten.
         */
        template<typename T1, typename T2, typename ...TOthers>
        constexpr T2 SetBits(T2 startValue, T1 value, size_t start, size_t length, T1 value2, size_t start2, size_t length2, TOthers... n)
        {
            return SetBits(SetBits(startValue, value2, start2, length2, n...), value, start, length);
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_HELPERS_H
