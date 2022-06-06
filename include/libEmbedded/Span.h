/**
 * @file Span.h
 * @author Giel Willemsen
 * @brief A simple 'wrapper' around a section of memory. Basically a iterator with a end but without specifying backing storage.
 * @version 0.1 2022-03-31 Initial version
 * @version 0.2 2022-04-02 Resolved issue with const T* not having constructor params as const_iterator, just iterator.
 * @version 0.3 2022-04-14 Addition of index operators.
 * @version 0.4 2022-05-30 Added missing stddef.h include for size_t.
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBEMBEDDED_SPAN_H
#define LIBEMBEDDED_SPAN_H

#include <stddef.h>

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
        Span(iterator start, size_t length) : spanStart(start), spanEnd(start + length) {}

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
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_SPAN_H
