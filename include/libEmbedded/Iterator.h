/**
 * @file Iterator.h
 * @author Giel Willemsen
 * @brief Helpers for dealing with iterators.
 * @version 0.1 2022-06-14 Imported iterator helpers from Span.h and added a FindStartOf helper to search in iterators.
 * @date 2022-06-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_ITERATOR_H
#define LIBEMBEDDED_ITERATOR_H
#include "stddef.h"
namespace libEmbedded
{
    /**
     * @brief Calculates the number of values between begin and end.
     *
     * @tparam TIter The type of the iterators.
     * @tparam TDiffType The type to count the distance in.
     * @param begin The starting point to start counting from.
     * @param end The iterator at which to stop counting.
     * @return TDiffType The number of element between. SIZE_MAX means the iterators were never equal.
     */
    template <typename TIter, typename TDiffType = size_t>
    constexpr TDiffType Distance(TIter begin, TIter end)
    {
        return begin == end ? 0 : Distance(++begin, end) + 1;
    }

    /**
     * @brief Computes the distance of a container (shorthand for Distance(cont.cbegin(), cont.cend()))
     *
     * @tparam TContainer The container type to get the distance from.
     * @tparam TDiffType The type to count the distance in.
     * @param container The container to get the distance between the begin and end iterator from.
     * @return TDiffType The number of element between. SIZE_MAX means the iterators were never equal.
     */
    template <typename TContainer, typename TDiffType = size_t>
    constexpr TDiffType Distance(const TContainer &container)
    {
        return Distance<typename TContainer::const_iterator, TDiffType>(container.cbegin(), container.cend());
    }

    /**
     * @brief Increments it n number of times.
     *
     * @tparam TIter The type of the iterator to increment.
     * @param it The iterator to increment.
     * @param n The number of times to increment it.
     */
    template <typename TIter>
    constexpr void Advance(TIter &it, size_t n = 1)
    {
        while (n > 0)
        {
            ++it;
            --n;
        }
    }

    /**
     * @brief Increments it n number of times and returns this iterator.
     *
     * @tparam TIter The type of the iterator to increment.
     * @param it The iterator to increment.
     * @param n The number of times to increment it.
     * @return TIter The iterator that was incremented n times.
     */
    template <typename TIter>
    constexpr TIter Next(TIter it, size_t n = 1)
    {
        return n == 0 ? it : Next(++it, n - 1);
    }

    /**
     * @brief Decrement it n number of times and returns this iterator.
     *
     * @tparam TIter The type of the iterator to decrement.
     * @param it The iterator to decrement.
     * @param n The number of times to decrement it.
     * @return TIter The iterator that was decremented n times.
     */
    template <typename TIter>
    constexpr TIter Prev(TIter it, size_t n = 1)
    {
        return n == 0 ? it : Prev(--it, n - 1);
    }

    /**
     * @brief Finds the key in the given haystack.
     *
     * @tparam TIter The type of the iterators to use.
     * @param hayStart The starting iterator for the haystack to search in.
     * @param hayEnd The end iterator of the haystack to search in.
     * @param keyStart The start iterator of the key to look for.
     * @param keyEnd The end iterator of the key to look for.
     * @param foundAt Set to the iterator in the haystack where the key was found.
     * @return true if the key was found in the iterator.
     * @return false if the key wasn't found in the iterator.
     */
    template <typename TIter>
    bool FindStartOf(TIter hayStart, TIter hayEnd, TIter keyStart, TIter keyEnd, TIter &foundAt)
    {
        if (hayStart == hayEnd || keyStart == keyEnd)
        {
            return false;
        }
        bool found = false;
        TIter it = hayStart;
        bool inMatch = false;
        while (found == false && it != hayEnd)
        {
            if (*it == *keyStart)
            {
                TIter checkIt = it;
                TIter keyIt = keyStart;
                bool isEqual = true;
                while (isEqual && keyIt != keyEnd && checkIt != hayEnd)
                {
                    isEqual = (*keyIt == *checkIt);
                    ++keyIt;
                    ++checkIt;
                }
                if (checkIt == hayEnd && keyIt != keyEnd) // End of hay reached before end of key so key never actually found.
                {
                    isEqual = false;
                }
                if (isEqual && keyIt == keyEnd)
                {
                    found = true;
                    foundAt = it;
                }
            }
            libEmbedded::Advance(it);
        }
        return found;
    }

    /**
     * @brief Finds the key in the given haystack.
     *
     * @tparam TContainer The type of the container for the haystack to search in.
     * @tparam TIter The type of the iterators to use.
     * @param container The container to use a haystack to search in.
     * @param keyStart The start iterator of the key to look for.
     * @param keyEnd The end iterator of the key to look for.
     * @param foundAt Set to the iterator in the haystack where the key was found.
     * @return true if the key was found in the container.
     * @return false if the key wasn't found in the container.
     */
    template <typename TContainer, typename TIter>
    bool FindStartOf(const TContainer &container, TIter keyStart, TIter keyEnd, TIter &foundAt)
    {
        static_assert(std::is_same<typename TContainer::const_iterator, TIter>::value, "The iterator type of the foundAt value is not the same as the container iterator.");
        return FindStartOf(container.begin(), container.end(), keyStart, keyEnd, foundAt);
    }

    /**
     * @brief Finds the key in the given haystack.
     *
     * @tparam THayContainer The type of the container for the haystack to search in.
     * @tparam TKeyContainer The type of the container for the key to search for.
     * @tparam TIter The type of the iterators to use.
     * @param container The container to use a haystack to search in.
     * @param key The container that represents the key that has to be found.
     * @param foundAt Set to the iterator in the haystack where the key was found.
     * @return true if the key was found in the container.
     * @return false if the key wasn't found in the container.
     */
    template <typename THayContainer, typename TKeyContainer, typename TIter>
    bool FindStartOf(const THayContainer &container, const TKeyContainer &key, TIter &foundAt)
    {
        static_assert(std::is_same<typename THayContainer::const_iterator, typename TKeyContainer::const_iterator>::value, "The iterator of the hay container and the key container should be the same.");
        static_assert(std::is_same<typename THayContainer::const_iterator, TIter>::value, "The iterator type of the foundAt value is not the same as the container iterator.");
        return FindStartOf(container.begin(), container.end(), key.begin(), key.end(), foundAt);
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_ITERATOR_H
