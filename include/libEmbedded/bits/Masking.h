/**
 * @file Masking.h
 * @author Giel Willemsen
 * @brief Some helper functions for helping with masking bits.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_MASKING_H
#define LIBEMBEDDED_BITS_MASKING_H
#include <stddef.h>
#include <stdint.h>

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
        constexpr T CreateMask(size_t bitLength, size_t startAtBit = 0)
        {
            T value = 0;
            for (size_t i = 0; i < bitLength; i++)
            {
                value <<= 1;
                value |= 1;
            }
            value = value << startAtBit;
            return value;
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
