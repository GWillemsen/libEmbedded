/**
 * @file Flags.h
 * @author Giel Willemsen
 * @brief Some helper functions for helping with bit flags.
 * @version 0.1 2022-10-28 Extract from original bits/helper.h file.
 * @version 0.2 2022-10-30 Added new helper to create flags from regular argument and not template args.
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_FLAGS_H
#define LIBEMBEDDED_BITS_FLAGS_H
#include <stddef.h>

namespace libEmbedded
{
    namespace bits
    {
        /**
         * @brief Create a value with the bit at the given position set.
         * 
         * @tparam T The type to create the mask in.
         * @tparam T2 The type of the value that provides the index of the bit to set.
         * @param position The index of the bit to set.
         * @return constexpr T The resulting value with the bit at position set.
         */
        template<typename T, typename T2>
        constexpr T CreateFlagSet(T2 position)
        {
            return ((T)1 << position);
        }

        /**
         * @brief Create a  value with the given bit indexes set.
         * 
         * @tparam T The type of the value to set the bits in.
         * @tparam T2 The type of the first index value.
         * @tparam T3 The type of the second index value.
         * @param position1 The position of the first bit to set.
         * @param position2 The position of the second bit to set.
         * @return constexpr T The resulting value with the two bits set.
         */
        template<typename T, typename T2, typename T3>
        constexpr T CreateFlagSet(T2 position1, T3 position2)
        {
            return CreateFlagSet<T>(position1) | CreateFlagSet<T>(position2);
        }

        /**
         * @brief Create a  value with the given bit indexes set.
         * 
         * @tparam T The type of the value to set the bits in.
         * @tparam T2 The type of the first index value.
         * @tparam TOthers The type of the other index values.
         * @param position The position of the first bit to set.
         * @param others The positions of the other bits to set.
         * @return constexpr T The resulting value with the bits set.
         */
        template<typename T, typename T2, typename... TOthers>
        constexpr T CreateFlagSet(T2 position, TOthers... others)
        {
            return CreateFlagSet<T>(position) | CreateFlagSet<T>(others...);
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

#endif // LIBEMBEDDED_BITS_FLAGS_H
