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

        constexpr Optional() : value(), isSet(false)
        {}
        
        Optional(const Optional& value) : value(), isSet(false)
        {
            if (value.IsSet())
            {
                Set(value.Get());
            }
        }

        explicit Optional(const T& value) : value(), isSet(false)
        {   
            Set(value);
        }

        explicit Optional(Optional&& other) : value(), isSet(false)
        {
            if (other.IsSet())
            {
                Set(std::move(other.Get()));
            }
            other.isSet = false;
        }

        ~Optional() noexcept(noexcept(this->DestructPresent()))
        {
            this->DestructPresent();
        }

        //
        // Accessors
        //

        const T& Get() const noexcept {
            return *GetPtr();
        }

        T& Get() noexcept {
            return *GetPtr();
        }

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
        // Presence checkers
        //
        
        bool IsSet() const noexcept {
            return this->isSet;
        }

        explicit operator bool() const noexcept {
            return this->isSet;
        }

        //
        // Setters
        //

        void Set(const T& value) noexcept(noexcept(DestructPresent()) && std::is_nothrow_copy_constructible<T>::value) {
            this->DestructPresent();
            new (GetPtr()) T(value);
            this->isSet = true;
        }

        void Set(T&& value) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_constructible<T>::value) {
            this->DestructPresent();
            new (GetPtr()) T(std::forward<T>(value));
            this->isSet = true;
        }

        Optional& operator=(const Optional& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_assignable<T, const T&>::value) {
            this->DestructPresent();
            if (other.IsSet()) {
                this->Get() = other.Get();
                this->isSet = true;
            }
            return *this;
        }

        Optional& operator=(Optional&& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_assignable<T>::value) {
            this->DestructPresent();
            if (other.IsSet()) {
                this->Get() = std::move(other.Get());
                this->isSet = true;
                other.isSet = false;
            }
            return *this;
        }

        Optional& operator=(const T& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_assignable<T, const T&>::value) {
            this->DestructPresent();
            this->Get() = other;
            this->isSet = true;
            return *this;
        }

        Optional& operator=(T&& other) noexcept(noexcept(DestructPresent()) && std::is_nothrow_move_assignable<T>::value) {
            this->DestructPresent();
            this->Get() = std::move(other);
            this->isSet = true;
            return *this;
        }
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_OPTIONAL_H
