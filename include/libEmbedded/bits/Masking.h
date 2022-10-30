/**
 * @file Masking.h
 * @author Giel Willemsen
 * @brief Some helper functions for helping with masking bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.2 2022-10-30 CreateMask is now a single statement function as well (+some weird behaviour, implementation defined??, on GCC with bit rolls on uint32_t's<<32 fixed in the process)
 * @version 0.3 2022-10-30 Added usage examples
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_MASKING_H
#define LIBEMBEDDED_BITS_MASKING_H
#include <stddef.h>
#include <stdint.h>
#include "libEmbedded/bits/Util.h"

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Set the count number of bits in the value.
         * 
         * Usage:
         * @code 
         * uint8_t a = SetNrBits<uint8_t>(4);
         * uint8_t b = SetNrBits<uint8_t>(5);
         * // a == 0x0F
         * // b == 0x1F
         * @endcode
         * 
         * @tparam T The type to set the bits in.
         * @param count The number of bits to set from the start.
         * @return constexpr T The value with count number of bits set.
         */
        template<typename T>
        constexpr T SetNrBits(size_t count)
        {
            return (count > 0 ? (1 | SetNrBits<T>(count - 1) << 1) : 0);
        }

        /**
         * @brief Create a mask of bitLength bits for type T.
         * 
         * Usage:
         * @code
         * uint8_t a = CreateMask<uint8_t>(3);
         * uint8_t b = SetNrBits<uint8_t>(3, 3);
         * // a == 0x07
         * // b == 0x38
         * @endcode
         * 
         * @tparam T The type to create the mask in.
         * @param bitLength The number of bits that are set starting at position 0.
         * @return T The resulting mask.
         */
        template<typename T = int>
        constexpr T CreateMask(size_t bitLength, size_t startAtBit = 0)
        {
            return SetNrBits<T>(bitLength) << startAtBit;
        }

        template<>
        constexpr uint8_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((uint_least16_t)1 << bitLength) - 1) << startAtBit;
        }

        template<>
        constexpr uint16_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((uint_least32_t)1 << bitLength) - 1) << startAtBit;
        }

        template<>
        constexpr uint32_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((uint_least64_t)1 << bitLength) - 1) << startAtBit;
        }

        template<>
        constexpr int8_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((int_least16_t)1 << bitLength) - 1) << startAtBit;
        }

        template<>
        constexpr int16_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((int_least32_t)1 << bitLength) - 1) << startAtBit;
        }

        template<>
        constexpr int32_t CreateMask(size_t bitLength, size_t startAtBit)
        {
            return (((int_least64_t)1 << bitLength) - 1) << startAtBit;
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_MASKING_H
