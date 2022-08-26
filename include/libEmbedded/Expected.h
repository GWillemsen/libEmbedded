/**
 * @file Expected.h
 * @author Giel Willemsen
 * @brief Represents a value that is usually present but sometimes it is not, and then adfana other type of value is given.
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

        ~Expected()
        {
            this->DestructValue();
        }

        const TExpected& GetExpected() const
        {
            return *GetPtr<TExpected>();
        }

        TExpected& GetExpected()
        {
            return *GetPtr<TExpected>();
        }

        const TAlternative& GetAlternative() const
        {
            return *GetPtr<TAlternative>();
        }

        TAlternative& GetAlternative()
        {
            return *GetPtr<TAlternative>();
        }

        bool HasExpected() const
        {
            return this->is_expected;
        }

        bool HasValue() const
        {
            return this->value_set;
        }

        static Expected FromExpected(const TExpected& expected)
        {
            Expected exp;
            exp.SetExpected(expected);
            return exp;
        }

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
