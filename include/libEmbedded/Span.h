/**
 * @file Span.h
 * @author Giel Willemsen
 * @brief A simple 'wrapper' around a section of memory. Basically a iterator with a end but without specifying backing storage.
 * @version 0.1 2022-03-31 Initial version
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBEMBEDDED_SPAN_H
#define LIBEMBEDDED_SPAN_H

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
        constexpr Span(iterator start, iterator end) : spanStart(start), spanEnd(end){};

        /**
         * @brief Construct a new span with the given start and length to end.
         * 
         * @param start The starting point of the span.
         * @param length The number of elements in the span.
         */
        Span(iterator start, size_t length) : spanStart(start), spanEnd(start + length) {}

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
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_SPAN_H
