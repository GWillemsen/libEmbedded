/**
 * @file Expected.h
 * @author Giel Willemsen
 * @brief Represents a value that is usually present but sometimes it is not, and then another type of value is given.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#ifndef LIBEMBEDDED_EXPECTED_H
#define LIBEMBEDDED_EXPECTED_H
#include <memory>

namespace libEmbedded
{

    /**
     * @brief Represent a value that usually present but a alternative value might be given instead.
     * WARNING: Accessors don't check if a given value is set. You need to check that a value is set, and if it is set, if it is a expected or alternative value.
     * 
     * @tparam TExpected 
     * @tparam TAlternative 
     */
    template<typename TExpected, typename TAlternative>
    class Expected
    {
    public:
        static constexpr size_t kMaxItemSize = sizeof(TExpected) > sizeof(TAlternative) ? sizeof(TExpected) : sizeof(TAlternative);
        using expected = TExpected;
        using alternative = TAlternative;
        using storage = std::aligned_storage<kMaxItemSize>;
    private:
        typename storage::type value;
        bool is_expected;
        bool value_set;

    public:

        /**
         * @brief Construct a new Expected object from a existing one.
         * 
         * @param other The other Expected object to copy.
         */
        Expected(const Expected& other) : value(), is_expected(other.is_expected), value_set(other.value_set)
        {
            if (!other.value_set)
            {
                return;
            }
            if (other.is_expected)
            {

                this->ConstructExpected(other.GetExpected());
            }
            else
            {
                this->ConstructAlternative(other.GetAlternative());
            }
        }

        /**
         * @brief Copy the value from the given Expected to the current and return the updated current.
         * 
         * @param other The other Expected to copy.
         * @return Expected& The current Expected itself.
         */
        Expected& operator=(const Expected& other)
        {
            if (this->value_set)
            {
                this->DestructValue();
                this->value_set = false;
                this->is_expected = false;
            }

            if (other.value_set)
            {
                if (other.is_expected)
                {
                    this->GetExpected() = other.GetExpected();
                }
                else
                {
                    this->GetAlternative() = other.GetAlternative();
                }
                this->is_expected = other.is_expected;
                this->value_set = true;
            }

            return *this;
        }

        /**
         * @brief Destroy this Expected object.
         * 
         */
        ~Expected()
        {
            this->DestructValue();
        }

        /**
         * @brief Get the expected value.
         * 
         * @return const TExpected& The current value as a expected value.
         */
        const TExpected& GetExpected() const
        {
            return *GetPtr<TExpected>();
        }

        /**
         * @brief Get the expected value.
         * 
         * @return const TExpected& The current value as a expected value.
         */
        TExpected& GetExpected()
        {
            return *GetPtr<TExpected>();
        }

        /**
         * @brief Get the Alternative object.
         * 
         * @return const TAlternative& The current value as a alternative value.
         */
        const TAlternative& GetAlternative() const
        {
            return *GetPtr<TAlternative>();
        }

        /**
         * @brief Get the Alternative object.
         * 
         * @return const TAlternative& The current value as a alternative value.
         */
        TAlternative& GetAlternative()
        {
            return *GetPtr<TAlternative>();
        }

        /**
         * @brief The value that is set is of the Expected type.
         * 
         * @return true The value that is set is a Expected value.
         * @return false Either there is no value set, or the value that is set is of the Alternative type.
         */
        bool HasExpected() const
        {
            return this->is_expected;
        }

        /**
         * @brief Check if this object has a value.
         * 
         * @return true If a value is set.
         * @return false If there is no value set.
         */
        bool HasValue() const
        {
            return this->value_set;
        }

        /**
         * @brief Construct a new Expected object from the a TExpected value.
         * 
         * @param expected The value to construct the expected value from.
         * @return Expected The resulting Expected object.
         */
        static Expected FromExpected(const TExpected& expected)
        {
            Expected exp;
            exp.SetExpected(expected);
            return exp;
        }

        /**
         * @brief Construct a new Expected object from the a TAlternative value.
         * 
         * @param expected The value to construct the expected value from.
         * @return Expected The resulting Expected object.
         */
        static Expected FromAlternative(const TAlternative& alternative)
        {
            Expected exp;
            exp.SetAlternative(alternative);
            return exp;
        }

    private:
        Expected() : value(), is_expected(false), value_set(false)
        {}

        void SetExpected(const TExpected& expected)
        {
            this->ConstructExpected(expected);
            is_expected = true;
            value_set = true;
        }

        void SetAlternative(const TAlternative& alternative)
        {
            this->ConstructAlternative(alternative);
            is_expected = false;
            value_set = true;
        }

        template<typename T>
        T* GetPtr() const
        {
            return reinterpret_cast<T*>((void*)&value);
        }

        void DestructValue()
        {
            if (this->value_set)
            {
                if (this->is_expected)
                {
                    this->GetPtr<TExpected>()->~TExpected();
                }
                else
                {
                    this->GetPtr<TAlternative>()->~TAlternative();
                }
            }
        }

        void ConstructExpected(const TExpected& expected)
        {
            new (GetPtr<TExpected>()) TExpected(expected);
        }
        
        void ConstructAlternative(const TAlternative& alternative)
        {
            new (GetPtr<TAlternative>()) TAlternative(alternative);
        }
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_EXPECTED_H
