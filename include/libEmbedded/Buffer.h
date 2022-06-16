/**
 * @file Buffer.h
 * @author Giel Willemsen
 * @brief Implement a buffer of a static size that drops elements the oldest elements once space runs out.
 * @version 0.1 2022-02-20 Initial version
 * @version 0.2 2022-06-16 Resolved a issue where the Remove method had a wrong memory offset in the buffer and would also reset the elementsUsed counter.
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LIBEMBEDDED_BUFFER_H
#define LIBEMBEDDED_BUFFER_H

#include <stddef.h>

namespace libEmbedded
{
    template <typename T, size_t TNumElements>
    class Buffer
    {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;

    private:
    public:
    private:
        char workspace[TNumElements * sizeof(T)];
        size_t elementsUsed;

    public:
        /**
         * @brief Construct a new empty rotating buffer.
         *
         */
        constexpr Buffer() : workspace{0}, elementsUsed(0) {}

        /**
         * @brief Copies the other buffer into this instance.
         *
         * @param other The buffer to copy from.
         */
        Buffer(const Buffer<T, TNumElements> &other);

        /**
         * @brief Copies the other buffer into this instance.
         *
         * @param other The buffer to copy from.
         */
        template <size_t TNumOtherElements>
        Buffer(const Buffer<T, TNumOtherElements> &other);

        /**
         * @brief Destroy the buffer.
         *
         */
        ~Buffer();

        /**
         * @brief Retrieve a modifiable iterator to the beginning of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The beginning of the buffer.
         */
        iterator begin();

        /**
         * @brief Retrieve a readonly iterator to the beginning of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The beginning of the buffer.
         */
        const_iterator begin() const;

        /**
         * @brief Retrieve a readonly iterator to the beginning of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The beginning of the buffer.
         */
        const_iterator cbegin() const;

        /**
         * @brief Retrieve a modifiable iterator to the end of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The end of the buffer.
         */
        iterator end();

        /**
         * @brief Retrieve a readonly iterator to the end of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The end of the buffer.
         */
        const_iterator end() const;

        /**
         * @brief Retrieve a readonly iterator to the end of the buffer.
         * @note Not according to naming standard because these are functions used by
         * the STL for allowing iterators to be used with STL libraries.
         *
         * @return The end of the buffer.
         */
        const_iterator cend() const;

        /**
         * @brief Remove the give number of items from the buffer.
         *
         * @param count The number of elements to drop from the buffer.
         */
        void Remove(size_t count);

        /**
         * @brief Adds the given element to the back of the buffer. Poping at the beginning if necessary.
         *
         * @param element The element to add to the buffer.
         */
        void Add(const T &element);

        /**
         * @brief Adds the given elements to the back of the buffer. Poping at the beginning if necessary.
         * If elementCount is more than fit in the buffer only the last items the given elements are actually copied and preserved.
         *
         * @param elements The elements to add to the buffer.
         * @param elementCount The number of elements to add to the buffer.
         */
        void AddRange(const T *elements, size_t elememtCount);

        /**
         * @brief Returns the number of elements that are present in the buffer.
         *
         * @return size_t The number of elements in the buffer.
         */
        size_t Size() const;

        /**
         * @brief Returns the maximum number of elements that could possibly be in the buffer.
         *
         * @return size_t The maximum number of elements possible in the buffer.
         */
        size_t Capacity() const;

        Buffer<T, TNumElements> &operator=(const Buffer<T, TNumElements> &other);

        /**
         * @brief Retrieve the element at the given index of the buffer.
         * Warning: No bounds check!
         *
         * @param index The index to get the item from.
         * @return The reference to the item at the given index.
         */
        T &operator[](size_t index);

        /**
         * @brief Retrieve a constant element at the given index of the buffer.
         * Warning: No bounds check!
         *
         * @param index The index to get the item from.
         * @return The constant reference to the item at the given index.
         */
        const T &operator[](size_t index) const;

        /**
         * @brief Retrieve the element at the given index of the buffer.
         * Warning: No bounds check!
         *
         * @param index The index to get the item from.
         * @return The reference to the item at the given index.
         */
        T &GetItem(size_t index);

        /**
         * @brief Retrieve a constant element at the given index of the buffer.
         * Warning: No bounds check!
         *
         * @param index The index to get the item from.
         * @return The constant reference to the item at the given index.
         */
        const T &GetItem(size_t index) const;

        template <size_t TOtherNumElements>
        bool operator==(const Buffer<T, TOtherNumElements> &other) const;

        template <size_t TOtherNumElements>
        bool operator!=(const Buffer<T, TOtherNumElements> &other) const;

    private:
        iterator GetIndexPointer(size_t index);

        const_iterator GetConstIndexPointer(size_t index) const;
    };

    template <typename T, size_t TNumElements>
    Buffer<T, TNumElements>::Buffer(const Buffer<T, TNumElements> &other)
    {
        for (size_t i = 0; i < other.elementsUsed; i++)
        {
            T *memory = GetIndexPointer(i);
            new (memory) T(other.GetItem(i));
        }
        this->elementsUsed = other.elementsUsed;
    }

    template <typename T, size_t TNumElements>
    template <size_t TNumOtherElements>
    Buffer<T, TNumElements>::Buffer(const Buffer<T, TNumOtherElements> &other)
    {
        static_assert(TNumOtherElements <= TNumElements, "TNumOtherElements must be of equal size or less than the targets buffer TNumElements.");
        // Size must be used because of TNumOtherElements we run into Private/Public issues with template instantation.
        for (size_t i = 0; i < other.Size(); i++)
        {
            T *memory = GetIndexPointer(i);
            new (memory) T(other.GetItem(i));
        }
        this->elementsUsed = other.Size();
    }

    template <typename T, size_t TNumElements>
    Buffer<T, TNumElements>::~Buffer()
    {
        for (size_t i = 0; i < this->elementsUsed; i++)
        {
            this->GetIndexPointer(i)->~T();
        }
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::iterator Buffer<T, TNumElements>::begin()
    {
        return this->GetIndexPointer(0);
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::const_iterator Buffer<T, TNumElements>::begin() const
    {
        return this->GetConstIndexPointer(0);
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::const_iterator Buffer<T, TNumElements>::cbegin() const
    {
        return this->GetConstIndexPointer(0);
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::iterator Buffer<T, TNumElements>::end()
    {
        return this->GetIndexPointer(this->elementsUsed);
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::const_iterator Buffer<T, TNumElements>::end() const
    {
        return this->GetConstIndexPointer(this->elementsUsed);
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::const_iterator Buffer<T, TNumElements>::cend() const
    {
        return this->GetConstIndexPointer(this->elementsUsed);
    }

    template <typename T, size_t TNumElements>
    void Buffer<T, TNumElements>::Remove(size_t count)
    {
        size_t removeCount = count;
        if (removeCount > this->Size())
        {
            removeCount = this->Size();
        }
        if (removeCount == this->Size())
        {
            memset(this->GetIndexPointer(0), 0, TNumElements * sizeof(T));
            this->elementsUsed = 0;
        }
        else
        {
            memcpy(this->GetIndexPointer(0), this->GetConstIndexPointer(removeCount), (this->Size() - removeCount) * sizeof(T));
            iterator newEnd = this->GetIndexPointer(this->Size());
            const size_t kSetItemCount = (TNumElements - this->Size());
            memset(newEnd, 0, kSetItemCount  * sizeof(T));
            this->elementsUsed -= removeCount;
        }
    }

    template <typename T, size_t TNumElements>
    void Buffer<T, TNumElements>::Add(const T &element)
    {
        if (this->Size() == this->Capacity())
        {
            this->Remove(1);
        }
        iterator location = this->GetIndexPointer(this->Size());
        new (location) T(element);
        this->elementsUsed++;
    }

    template <typename T, size_t TNumElements>
    void Buffer<T, TNumElements>::AddRange(const T *elements, size_t elementCount)
    {
        const T *start = elements;
        size_t count = elementCount;
        if (elementCount > this->Capacity())
        {
            size_t diff = elementCount - this->Capacity();
            start += diff;
            count -= diff;
        }
        if (count > this->Capacity() - this->Size())
        {
            size_t toRemove = count - (this->Capacity() - this->Size());
            this->Remove(toRemove);
        }
        for (size_t i = 0; i < count; i++)
        {
            new (GetIndexPointer(Size())) T(start[i]);
            this->elementsUsed++;
        }
    }

    template <typename T, size_t TNumElements>
    size_t Buffer<T, TNumElements>::Size() const
    {
        return this->elementsUsed;
    }

    template <typename T, size_t TNumElements>
    size_t Buffer<T, TNumElements>::Capacity() const
    {
        return TNumElements;
    }

    template <typename T, size_t TNumElements>
    Buffer<T, TNumElements> &Buffer<T, TNumElements>::operator=(const Buffer<T, TNumElements> &other)
    {
        this->Remove(this->elementsUsed);
        this->AddRange(other.GetConstIndexPointer(0), other.elementsUsed);
        return *this;
    }

    template <typename T, size_t TNumElements>
    T &Buffer<T, TNumElements>::operator[](size_t index)
    {
        return this->GetItem(index);
    }

    template <typename T, size_t TNumElements>
    const T &Buffer<T, TNumElements>::operator[](size_t index) const
    {
        return this->GetItem(index);
    }

    template <typename T, size_t TNumElements>
    T &Buffer<T, TNumElements>::GetItem(size_t index)
    {
        return *this->GetIndexPointer(index);
    }

    template <typename T, size_t TNumElements>
    const T &Buffer<T, TNumElements>::GetItem(size_t index) const
    {
        return *this->GetConstIndexPointer(index);
    }

    template <typename T, size_t TNumElements>
    template <size_t TOtherNumElements>
    bool Buffer<T, TNumElements>::operator==(const Buffer<T, TOtherNumElements> &other) const
    {
        if (this->Size() != other.Size())
        {
            return false;
        }
        for (size_t i = 0; i < this->elementsUsed; i++)
        {
            if (this->GetItem(i) != other.GetItem(i))
            {
                return false;
            }
        }
        return true;
    }

    template <typename T, size_t TNumElements>
    template <size_t TOtherNumElements>
    bool Buffer<T, TNumElements>::operator!=(const Buffer<T, TOtherNumElements> &other) const
    {
        if (this->Size() != other.Size())
        {
            return true;
        }

        bool allmatch = true;
        for (size_t i = 0; i < other.Size(); i++)
        {
            if (this->GetItem(i) != other.GetItem(i))
            {
                allmatch = false;
                break;
            }
        }

        return !allmatch;
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::iterator Buffer<T, TNumElements>::GetIndexPointer(size_t index)
    {
        return iterator(this->workspace + (sizeof(T) * index));
    }

    template <typename T, size_t TNumElements>
    typename Buffer<T, TNumElements>::const_iterator Buffer<T, TNumElements>::GetConstIndexPointer(size_t index) const
    {
        return const_iterator(this->workspace + (sizeof(T) * index));
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_BUFFER_H
