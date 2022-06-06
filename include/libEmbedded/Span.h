/**
 * @file Span.h
 * @author Giel Willemsen
 * @brief A simple 'wrapper' around a section of memory. Basically a iterator with a end but without specifying backing storage.
 * @version 0.1 2022-03-31 Initial version
 * @version 0.2 2022-04-02 Resolved issue with const T* not having constructor params as const_iterator, just iterator.
 * @version 0.3 2022-04-14 Addition of index operators.
 * @version 0.4 2022-05-30 Added missing stddef.h include for size_t.
 * @version 0.5 2022-06-06 Added DistanceApart to Span.
 * @version 0.6 2022-06-06 Moved DistanceApart to namespace as Distance and added a Advance.
 * @version 0.7 2022-06-06 Addition of equality check operators for Span.
 * @version 0.8 2022-06-06 Addition of shorthand function to get distance for container.
 * @version 0.9 2022-06-06 Addition of equality operators for const vs non-const but still of same type. And copy constructor to go from non-const to const version of same type.
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBEMBEDDED_SPAN_H
#define LIBEMBEDDED_SPAN_H

#include <stddef.h>
#include "math.h"

namespace libEmbedded
{
    /*
     * @brief A span that represents a sequence of elements that can only be read.
     * 
     * @tparam T The type of the element.
     * @tparam TIterator The iterator used to do a modifiable iteration.
     * @tparam TConstIterator The iterator used to do a readonly iteration.
     */
    template <typename T, typename TIterator = T*, typename TConstIterator = const T*>
    // I found no better alternative because if you do TConstIterator = const TIterator, using const_iterator = TConstIterator will complain because you made the whole iterator const not just the T. 
    struct Span
    {
        friend Span<const T, TIterator, TConstIterator>;
    public:
        using iterator = TIterator;
        using const_iterator = TConstIterator;
    private:

    public:
    private:
        iterator spanStart;
        iterator spanEnd;

    public:
        /**
         * @brief Constructs a new span with the given start and end points.
         * 
         * @param start The starting point of the span.
         * @param end The end point of the span.
         */
        constexpr Span(iterator start, iterator end) : spanStart(start), spanEnd(end){};

        /**
         * @brief Construct a new span with the given start and length to end.
         * 
         * @param start The starting point of the span.
         * @param length The number of elements in the span.
         */
        constexpr Span(iterator start, size_t length) : spanStart(start), spanEnd(start + length) {}

        /**
         * @brief Retrieve a iterator that starts at the beginning and can modify the span.
         * 
         * @return iterator The iterator at the start that can modify the span.
         */
        iterator begin()
        {
            return spanStart;
        }

        /**
         * @brief Retrieve a readonly iterator to the start of the span.
         * 
         * @return const_iterator The iterator at the start that can only read the span.
         */
        const_iterator begin() const
        {
            return spanStart;
        }

        /**
         * @brief Retrieve a readonly iterator to the start of the span.
         * 
         * @return const_iterator The iterator at the start that can only read the span.
         */
        const_iterator cbegin() const
        {
            return spanStart;
        }

        /**
         * @brief Retrieve a iterator that is 1 passed the last item in the span.
         * 
         * @return iterator A iterator that can modify the span that is one passed the last element in the span.
         */
        iterator end()
        {
            return spanEnd;
        }

        /**
         * @brief Retrieve a readonly iterator that is 1 passed the last item in the span.
         * 
         * @return iterator A iterator that can only read the span that is one passed the last element in the span.
         */
        const_iterator end() const
        {
            return spanEnd;
        }

        /**
         * @brief Retrieve a readonly iterator that is 1 passed the last item in the span.
         * 
         * @return iterator A iterator that can only read the span that is one passed the last element in the span.
         */
        const_iterator cend() const
        {
            return spanEnd;
        }

        /**
         * @brief Retrieve the item at the given index. Does not do any bounds checks!
         * 
         * @param index The index to retrieve the item from.
         * @return const T& A readonly reference to the item at the given index.
         */
        const T& operator[](size_t index) const
        {
            auto it = cbegin();
            size_t i = index;
            while(i > 0)
            {
                --i;
                ++it;
            }
            return *it;
        }

        /**
         * @brief Retrieve the item at the given index. Does not do any bounds checks!
         * 
         * @param index The index to retrieve the item from.
         * @return const T& A readonly reference to the item at the given index.
         */
        T& operator[](size_t index)
        {
            auto it = begin();
            size_t i = index;
            while(i > 0)
            {
                --i;
                ++it;
            }
            return *it;
        }

        /**
         * @brief Compares this span to the other span for value equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span represent the same start & end iterators.
         * @return false if the span have different start and/or end iterators.
         */
        bool operator==(const Span<T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart == other.spanStart && this->spanEnd == other.spanEnd;
        }
        
        /**
         * @brief Compares this span to the other span for value in-equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span have different start and/or end iterators.
         * @return false if the span represent the same start & end iterators.
         */
        bool operator!=(const Span<T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart != other.spanStart || this->spanEnd != other.spanEnd;
        }

        /**
         * @brief Compares this span to the other span for value equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span represent the same start & end iterators.
         * @return false if the span have different start and/or end iterators.
         */
        bool operator==(const Span<const T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart == other.spanStart && this->spanEnd == other.spanEnd;
        }
        
        /**
         * @brief Compares this span to the other span for value in-equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span have different start and/or end iterators.
         * @return false if the span represent the same start & end iterators.
         */
        bool operator!=(const Span<const T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart != other.spanStart || this->spanEnd != other.spanEnd;
        }
    };

    /**
     * @brief A span that represents a sequence of elements that can only be read.
     * 
     * @tparam T The type of the element.
     * @tparam TIterator The iterator used to do a modifiable iteration.
     * @tparam TConstIterator The iterator used to do a readonly iteration.
     */
    template <typename T, typename TIterator, typename TConstIterator>
    struct Span<const T, TIterator, TConstIterator>
    {
        friend Span<T, TIterator, TConstIterator>;
    public:
        using const_iterator = TConstIterator;
    private:

    public:
    private:
        const_iterator spanStart;
        const_iterator spanEnd;

    public:
        /**
         * @brief Constructs a new span with the given start and end points.
         * 
         * @param start The starting point of the span.
         * @param end The end point of the span.
         */
        constexpr Span(const_iterator start, const_iterator end) : spanStart(start), spanEnd(end){};

        /**
         * @brief Construct a new span with the given start and length to end.
         * 
         * @param start The starting point of the span.
         * @param length The number of elements in the span.
         */
        Span(const_iterator start, size_t length) : spanStart(start), spanEnd(start + length) {}

        /**
         * @brief Construct a new span from the given one.
         * 
         * @param span The span to create this one from.
         */
        Span(Span<T, TIterator, TConstIterator> span) : spanStart(span.cbegin()), spanEnd(span.cend()) {}

        /**
         * @brief Construct a new span from the given one.
         * 
         * @param span The span to create this one from.
         */
        Span(const Span<const T, TIterator, TConstIterator>& span) : spanStart(span.cbegin()), spanEnd(span.cend()) {}

        /**
         * @brief Retrieve a readonly iterator to the start of the span.
         * 
         * @return const_iterator The iterator at the start that can only read the span.
         */
        const_iterator begin() const
        {
            return spanStart;
        }

        /**
         * @brief Retrieve a readonly iterator to the start of the span.
         * 
         * @return const_iterator The iterator at the start that can only read the span.
         */
        const_iterator cbegin() const
        {
            return spanStart;
        }

        /**
         * @brief Retrieve a readonly iterator that is 1 passed the last item in the span.
         * 
         * @return iterator A iterator that can only read the span that is one passed the last element in the span.
         */
        const_iterator end() const
        {
            return spanEnd;
        }

        /**
         * @brief Retrieve a readonly iterator that is 1 passed the last item in the span.
         * 
         * @return iterator A iterator that can only read the span that is one passed the last element in the span.
         */
        const_iterator cend() const
        {
            return spanEnd;
        }

        /**
         * @brief Retrieve the item at the given index. Does not do any bounds checks!
         * 
         * @param index The index to retrieve the item from.
         * @return const T& A readonly reference to the item at the given index.
         */
        const T& operator[](size_t index) const
        {
            auto it = begin();
            size_t i = index;
            while(i > 0)
            {
                --i;
                ++it;
            }
            return *it;
        }
        
        /**
         * @brief Compares this span to the other span for value equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span represent the same start & end iterators.
         * @return false if the span have different start and/or end iterators.
         */
        bool operator==(const Span<T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart == other.spanStart && this->spanEnd == other.spanEnd;
        }
        
        /**
         * @brief Compares this span to the other span for value in-equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span have different start and/or end iterators.
         * @return false if the span represent the same start & end iterators.
         */
        bool operator!=(const Span<T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart != other.spanStart || this->spanEnd != other.spanEnd;
        }

        /**
         * @brief Compares this span to the other span for value equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span represent the same start & end iterators.
         * @return false if the span have different start and/or end iterators.
         */
        bool operator==(const Span<const T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart == other.spanStart && this->spanEnd == other.spanEnd;
        }
        
        /**
         * @brief Compares this span to the other span for value in-equality.
         * 
         * @param other The other span to compare to.
         * @return true if the span have different start and/or end iterators.
         * @return false if the span represent the same start & end iterators.
         */
        bool operator!=(const Span<const T, TIterator, TConstIterator> &other) const
        {
            return this->spanStart != other.spanStart || this->spanEnd != other.spanEnd;
        }
    };

    /**
     * @brief Calculates the number of values between begin and end.
     * 
     * @tparam TIter The type of the iterators.
     * @tparam TDiffType The type to count the distance in.
     * @param begin The starting point to start counting from.
     * @param end The iterator at which to stop counting.
     * @return TDiffType The number of element between. SIZE_MAX means the iterators were never equal.
     */
    template<typename TIter, typename TDiffType = size_t>
    constexpr TDiffType Distance(TIter begin, TIter end)
    {
        TIter it = begin;
        TDiffType i = 0;
        while(it != end && i < SIZE_MAX)
        {
            ++it;
            ++i;
        }
        return i;
    }

    /**
     * @brief Computes the distance of a container (shorthand for Distance(cont.cbegin(), cont.cend()))
     * 
     * @tparam TContainer The container type to get the distance from.
     * @tparam TDiffType The type to count the distance in.
     * @param container The container to get the distance between the begin and end iterator from.
     * @return TDiffType The number of element between. SIZE_MAX means the iterators were never equal. 
     */
    template<typename TContainer, typename TDiffType = size_t>
    constexpr TDiffType Distance(const TContainer& container)
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
    template<typename TIter>
    constexpr void Advance(TIter& it, size_t n)
    {
        while(n > 0)
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
    template<typename TIter>
    constexpr TIter Next(TIter it, size_t n = 1)
    {
        while(n > 0)
        {
            ++it;
            --n;
        }
        return it;
    }
    
    /**
     * @brief Decrement it n number of times and returns this iterator.
     * 
     * @tparam TIter The type of the iterator to decrement.
     * @param it The iterator to decrement.
     * @param n The number of times to decrement it.
     * @return TIter The iterator that was decremented n times.
     */
    template<typename TIter>
    constexpr TIter Prev(TIter it, size_t n = 1)
    {
        while(n > 0)
        {
            --it;
            --n;
        }
        return it;
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_SPAN_H
