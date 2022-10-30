/**
 * @file Util.h
 * @author Giel Willemsen
 * @brief Some helper bit functions that don't really fit in one of the other categories and don't have their own.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.2 2022-10-30 Added usage examples
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_UTIL_H
#define LIBEMBEDDED_BITS_UTIL_H
#include <stddef.h>
#include <limits.h>

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Get the size of the object type in bits.
         * 
         * Usage:
         * @code 
         * size_t a = SetNrBits<uint8_t>();
         * size_t b = SetNrBits<uint32_t>();
         * // a == 8
         * // b == 32
         * @endcode
         * 
         * @tparam T The type to get the memory size of.
         * @return constexpr size_t The number of bits needed to represent this type in memory.
         */
        template<typename T>
        constexpr size_t GetBitSize()
        {
            return sizeof(T) * CHAR_BIT;
        }
    } // namespace bits
} // namespace libEmbedded

#endif // LIBEMBEDDED_BITS_UTIL_H
