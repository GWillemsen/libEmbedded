/**
 * @file Optional.h
 * @author Giel Willemsen
 * @brief A value that can optionally contain a value but doesn't have to.
 * @version 0.1
 * @date 2022-08-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_OPTIONAL_H
#define LIBEMBEDDED_OPTIONAL_H

#include <memory>
#include <utility>

namespace libEmbedded
{
    template <typename T>
    class Optional
    {
    private:
        using storage = std::aligned_storage<sizeof(T)>;

    private:
        typename storage::type value;
        bool isSet;

    private:
        T* GetPtr() const noexcept
        {
            return reinterpret_cast<T*>((void*)&value);
        }

        void DestructPresent() noexcept(std::is_nothrow_default_constructible<T>::value) {
            if (this->isSet) {
                GetPtr()->~T();
                this->isSet = false;
            }
        }

    public:
        //
        // Constructors & Destructors
        //

        /**
         * @brief Construct a new empty Optional object.
         * 
         */
        constexpr Optional() : value(), isSet(false)
        {}
        
        /**
         * @brief Copy construct a new Optional object.
         * 
         * @param value The Optional to copy.
         */
        Optional(const Optional& value) : value(), isSet(false)
        {
            if (value.IsSet())
            {
                Set(value.Get());
            }
        }

        /**
         * @brief Construct a new set Optional object from the given value.
         * 
         * @param value The value to copy construct into this Optional.
         */
        explicit Optional(const T& value) : value(), isSet(false)
        {   
            Set(value);
        }

        /**
         * @brief Move construct a new Optional object from the given object.
         * 
         * @param other The object to move into this Optional.
         */
        explicit Optional(Optional&& other) : value(), isSet(false)
        {
            if (other.IsSet())
            {
                Set(std::move(other.Get()));
            }
            other.isSet = false;
        }

        /**
         * @brief Destroy the Optional object and object stored inside if present.
         * 
         */
        ~Optional() noexcept(noexcept(this->DestructPresent()))
        {
            this->DestructPresent();
        }

        //
        // Accessors methods
        //

        /**
         * @brief Retrieve the current value as type T. WARNING: No check if a value is actually stored in the object is done. Use IsSet to check this first.
         * 
         * @return const T& A reference to the current item stored.
         */
        const T& Get() const noexcept {
            return *GetPtr();
        }

        /**
         * @brief Retrieve the current value as type T. WARNING: No check if a value is actually stored in the object is done. Use IsSet to check this first.
         * 
         * @return T& A reference to the current item stored.
         */
        T& Get() noexcept {
            return *GetPtr();
        }

        //
        // Accessors operators
        //

        T* operator->() noexcept {
            return GetPtr();
        }

        const T* operator->() const noexcept {
            return GetPtr();
        }

        T& operator*() noexcept {
            return *GetPtr();
        }

        const T& operator*() const noexcept {
            return *GetPtr();
        }

        //
        // Presence check methods
        //
        
        /**
         * @brief Retrieve if a value is set.
         * 
         * @return true if a value was Set()
         * @return false if no value was set (and object accesses are therefore invalid and undefined behaviour).
         */
        bool IsSet() const noexcept {
            return this->isSet;
        }

        //
        // Presence check operators
        //

        explicit operator bool() const noexcept {
            return this->isSet;
        }

        //
        // Setter methods
        //

        /**
         * @brief Copy constructs the given value into this Optional.
         * 
         * @param value The value to copy into this Optional.
         */
        void Set(const T& value) noexcept(noexcept(DestructPresent()) && std::is_nothrow_copy_constructible<T>::value) {
            this->DestructPresent();
            new (GetPtr()) T(value);
            this->isSet = true;
        }

        /**
         * @brief Move constructs the given value into this Optional.
         * 
         * @param value The value to move into this Optional.
         */
        void Set(T&& value) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_constructible<T>::value) {
            this->DestructPresent();
            new (GetPtr()) T(std::forward<T>(value));
            this->isSet = true;
        }
        
        //
        // Setter operators
        //

        /**
         * @brief Copy assign the given Optional.
         * 
         * @param other The other optional to copy assign into this one.
         * @return Optional& The current Optional with the other copied into this one.
         */
        Optional& operator=(const Optional& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_assignable<T, const T&>::value) {
            this->DestructPresent();
            if (other.IsSet()) {
                this->Get() = other.Get();
                this->isSet = true;
            }
            return *this;
        }

        /**
         * @brief Move assign the given Optional into this one.
         * 
         * @param other The other Optional to move into this one.
         * @return Optional& The current Optional that the other is moved in.
         */
        Optional& operator=(Optional&& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_assignable<T>::value) {
            this->DestructPresent();
            if (other.IsSet()) {
                this->Get() = std::move(other.Get());
                this->isSet = true;
                other.isSet = false;
            }
            return *this;
        }

        /**
         * @brief (Copy) Assign the given value T to the current one.
         * 
         * @param other The value to assign the current value.
         * @return Optional& The current Optional that has it's value set to other.
         */
        Optional& operator=(const T& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_assignable<T, const T&>::value) {
            this->DestructPresent();
            this->Get() = other;
            this->isSet = true;
            return *this;
        }

        /**
         * @brief Move assign (or construct if none set yet) the given value T into the current one.
         * 
         * @param other The value to move into the current one.
         * @return Optional& The current Optional that has the other value moved into it.
         */
        Optional& operator=(T&& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value) {
            this->DestructPresent();
            this->Get() = std::move(other);
            this->isSet = true;
            return *this;
        }
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_OPTIONAL_H
