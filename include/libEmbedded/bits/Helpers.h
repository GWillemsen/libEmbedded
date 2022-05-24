/**
 * @file Helpers.h
 * @author Giel Willemsen (g.willemsen@student.fontys.nl)
 * @brief Some helper functions for manipulating bits.
 * @version 0.1
 * @date 2022-05-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_HELPERS_H
#define LIBEMBEDDED_BITS_HELPERS_H
#include "stddef.h"
#include "stdint.h"

namespace libEmbedded
{
    namespace bits
    {
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
         * @brief Copies bitCount nr of bits from source to destination with the given bit offsets without any internal buffering. 
         * Overlapping is allowed (destination and source can be the same with different offsets).
         * 
         */
        void MoveWithOffset(void* destination, size_t destinationBitOffset, void* source, size_t sourceBitOffset, size_t bitCount);
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_HELPERS_H
