/**
 * @file Pointer.h
 * @author Giel Willemsen
 * @brief Small utilty for automatically freeing a pointer when it leaves the scope.
 * @version 0.1 Initial version
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#ifndef LIBEMBEDDED_POINTER_H
#define LIBEMBEDDED_POINTER_H
#include "libEmbedded/TypeTrait.h"

namespace libEmbedded
{
    /**
     * @brief Pointer that allocated on the heap and should be deleted when out of scope.
     * NOTE: This type can't be assigned or copy constructed to prevent multiple deallocation events
     * for the same pointer.
     * 
     * @tparam T The actual type of the variable to have a pointer to.
     * @tparam TIsArray Free the pointer using `delete[] ptr` instead of `delete ptr` even if T is not detected as a array.
     * @tparam TIsNoArray Free the pointer using `delete ptr` instead of `delete[] ptr` even if T is detected as a array.
     */
    template<typename T, bool TIsArray = false, bool TIsNoArray = false>
    class LocalPointer
    {
        static_assert(!(TIsArray && TIsNoArray), "Either free using delete or delete[], but you can't select both!");
    public:
        using ItemType = typename libEmbedded::remove_extent<T>::type;
        using PointerType = ItemType*;

    private:
        PointerType ptr;

    private:

        template<typename C = T>
        typename libEmbedded::enable_if<(!libEmbedded::is_array<C>::value || TIsNoArray) && !TIsArray, void>::type Destruct()
        {
            delete ptr;
        }
    
        template<typename C = T>
        typename libEmbedded::enable_if<(libEmbedded::is_array<C>::value || TIsArray) && !TIsNoArray, void>::type Destruct()
        {
            delete[] ptr;
        }

    public:
        /**
         * @brief Construct a new pointer object
         * 
         * @param pointer The pointer to free when this object is out of scope.
         */
        explicit LocalPointer(PointerType pointer) : ptr(pointer)
        {}

        /**
         * @brief Don't allow a copy constructor as this will give problems as to when which one can delete the pointer.
         * 
         */
        LocalPointer(const LocalPointer<T>& ) = delete;

        /**
         * @brief Don't allow a copy constructor as this will give problems as to when which one can delete the pointer.
         * 
         */
        LocalPointer<T>& operator=(const LocalPointer<T>&) = delete;

        /**
         * @brief Move a old LocalPointer object into this one.
         * 
         * This is allowed because the old LocalPointer can now no longer free the pointer 
         * (which with C++ Move semantics is good defined behavior).
         */
        LocalPointer(LocalPointer<T>&& other) : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }

        PointerType operator->() const
        {
            return ptr;
        }

        ItemType& operator*() const
        {
            return *ptr;
        }

        PointerType Get() const
        {
            return ptr;
        }
        
        ~LocalPointer()
        {
            Destruct();
        }
    };

} // namespace libEmbedded

#endif // LIBEMBEDDED_POINTER_H
