/**
 * @file Helpers.h
 * @author Giel Willemsen (g.willemsen@student.fontys.nl)
 * @brief Some helper functions for manipulating bits.
 * @version 0.1 2022-05-22 Initial version
 * @version 0.2 2022-05-27 Added GetBitSize helper.
 * @version 0.3 2022-05-28 Added ExtractBits helper.
 * @version 0.4 2022-05-28 Added GetCombinedValue & CombineBitValues helper.
 * @version 0.5 2022-06-07 Added HasFlagSet to be able to quickly check what bits are set.
 * @date 2022-06-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_HELPERS_H
#define LIBEMBEDDED_BITS_HELPERS_H
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Create a mask of bitLength bits for type T.
         * 
         * @tparam T The type to create the mask in.
         * @param bitLength The number of bits that are set starting at position 0.
         * @return T The resulting mask.
         */
        template<typename T = int>
        constexpr T CreateMask(size_t bitLength)
        {
            T value = 0;
            for (size_t i = 0; i < bitLength; i++)
            {
                value <<= 1;
                value |= 1;
            }
            return value;
        }

        template<>
        constexpr uint8_t CreateMask(size_t bitLength)
        {
            return ((uint_least16_t)1 << bitLength) - 1;
        }

        template<>
        constexpr uint16_t CreateMask(size_t bitLength)
        {
            return ((uint_least32_t)1 << bitLength) - 1;
        }

        template<>
        constexpr uint32_t CreateMask(size_t bitLength)
        {
            return ((uint_least64_t)1 << bitLength) - 1;
        }

        template<>
        constexpr int8_t CreateMask(size_t bitLength)
        {
            return ((int_least16_t)1 << bitLength) - 1;
        }

        template<>
        constexpr int16_t CreateMask(size_t bitLength)
        {
            return ((int_least32_t)1 << bitLength) - 1;
        }

        template<>
        constexpr int32_t CreateMask(size_t bitLength)
        {
            return ((int_least64_t)1 << bitLength) - 1;
        }

        /**
         * @brief Get the size of the object type in bits.
         * 
         * @tparam T The type to get the memory size of.
         * @return constexpr size_t The number of bits needed to represent this type in memory.
         */
        template<typename T>
        constexpr size_t GetBitSize()
        {
            return sizeof(T) * CHAR_BIT;
        }

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
         * @brief Read value 1 & 2 as a continuous memory section in essence and extract nrOfBits bits starting at startOffsetBits from them.
         * 
         * @tparam T1 The type of the first value.
         * @tparam T2 The type of the second value.
         * @tparam T3 The return value type (decides how many bits can be returned!)
         * @param value1 The value to start extracting bits from.
         * @param value2 The second place to start extracting from if not enough bits in value 1.
         * @param startOffsetBits At what offset to start extracting bits in value 1.
         * @param nrOfBits The total number of bits to extract ()
         * @return constexpr T3 
         */
        template<typename T1, typename T2, typename T3 = uint32_t>
        constexpr T3 GetCombinedValue(T1 value1, T2 value2, size_t startOffsetBits, size_t nrOfBits)
        {
            constexpr size_t kBitsInT1 = GetBitSize<T1>();
            constexpr size_t kBitsInT2 = GetBitSize<T2>();
            constexpr size_t kBitsInT3 = GetBitSize<T3>();

            const bool kSkipVal1            = startOffsetBits > kBitsInT1;
            const size_t kBitsIn1           = kSkipVal1 ? 0 : kBitsInT1 - startOffsetBits;
            const size_t kBitsOffsetValue1  = kSkipVal1 ? 0 : startOffsetBits;
            const size_t kBitsOffsetValue2  = kSkipVal1 ? startOffsetBits - kBitsInT1 : 0;
            const size_t kBitsLeftAfterVal1 = nrOfBits - kBitsIn1;
            const size_t kBitsFrom2         = kBitsLeftAfterVal1 > kBitsInT2 ? kBitsInT2 : kBitsLeftAfterVal1;
            return CombineBitValues<T1, T2, T3>(value1, value2, kBitsOffsetValue1, kBitsIn1, kBitsOffsetValue2, kBitsFrom2);
        }

        /**
         * @brief Create a value with the bit at the given position set.
         * 
         * @tparam T The type to create the mask in.
         * @param TPosition The position of the bit to set.
         * @return constexpr T The resulting value with the bit at position set.
         */
        template<typename T, size_t TPosition>
        constexpr T CreateFlagSet()
        {
            return ((T)1 << TPosition);
        }

        /**
         * @brief Create a value with the bit at the given positions set.
         * 
         * @tparam T The type to create the mask in.
         * @tparam TPosition1 Position of the first bit position 1 to set.
         * @tparam TPosition2 Position of the second bit 2 to set.
         * @tparam TPositions The other positions to also set.
         * @return constexpr T The resulting value with the bit at position set.
         */
        template<typename T, size_t TPosition1, size_t TPosition2, size_t... TPositions>
        constexpr T CreateFlagSet()
        {
            return CreateFlagSet<T, TPosition1>() | CreateFlagSet<T, TPosition2, TPositions...>();
        }

        /**
         * @brief Check if the bit at position in value is set.
         * 
         * @tparam T The type of the value to check the bit in.
         * @param value The vale to check the bit in.
         * @param position The 0-indexed bit position to check.
         * @return true If the bit was set.
         * @return false If the bit was cleared.
         */
        template<typename T>
        constexpr bool HasFlagSet(T value,size_t position)
        {
            return (value & ((T)1 << position)) != 0;
        }

        /**
         * @brief Checks if all the given bit indexes are set in the value.
         * 
         * @tparam T The type of the value to check the bits in.
         * @tparam TPositions The type of the bit indexes to check.
         * @param value The value to check the bits in.
         * @param position The 0-index of the first bit to check.
         * @param position2 The 0-index of the second bit to check.
         * @param positions The 0-index of any optional other bits to check.
         * @return true If all the bits are set.
         * @return false If one or all of the bits are cleared.
         */
        template<typename T, typename ...TPositions>
        constexpr bool HasFlagSet(T value, size_t position, size_t position2, TPositions... positions)
        {
            return HasFlagSet(value, position) && HasFlagSet(value, position2, positions...);
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_HELPERS_H
