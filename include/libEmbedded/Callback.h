/**
 * @file Callback.h
 * @author Giel Willemsen
 * @brief Wrapper for a function pointer with a userdata parameter.
 * @version 0.1 2022-02-07 Initial version
 * @version 0.1 2022-03-09 Addition of specific Invoke method.
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBEMBEDDED_CALLBACK_H
#define LIBEMBEDDED_CALLBACK_H

namespace libEmbedded
{
    /**
     * @brief A wrapper class for a function pointer with a optional userdata pointer.
     *
     * @tparam TCallback The function pointer for this callback.
     */
    template <typename TCallback, typename TContext = void, typename TReturnType = void>
    class Callback
    {
    private:
        TCallback call;
        TContext *usrdata;

    public:
        /**
         * @brief Create a new empty callback.
         *
         */
        constexpr Callback() : call(nullptr), usrdata(nullptr) {}

        /**
         * @brief Create a new callback reploaded with the given callback and userdata.
         *
         * @param callback The callback to preload the instance with.
         * @param userdata The optional userdata for the callback when called.
         */
        constexpr Callback(TCallback callback, TContext *userdata) : call(callback), usrdata(userdata) {}

        /**
         * @brief Check if the callback is set and can be called or not.
         *
         * @return true If the callback can be called.
         * @return false If the callback is NOT set and therefore cannot (or better shouldn't) be called.
         */
        bool IsSet() const;

        /**
         * @brief Set the callback function and its optional userdata.
         *
         * @param callback The callback to handle the invoke.
         * @param userdata Optional userdata that is given to the callback when called.
         */
        void SetCallback(TCallback callback, TContext *userdata = nullptr);

        /**
         * @brief Invoke the callback itself.
         *
         * @tparam TArgs The type of the arguments for the callback.
         * @param args The arguments for the callback (excluding the userdata).
         */
        template <typename... TArgs>
        TReturnType Invoke(TArgs... args) const;

        /**
         * @brief Invoke the callback itself.
         *
         * @tparam TArgs The type of the arguments for the callback.
         * @param args The arguments for the callback (excluding the userdata).
         */
        template <typename... TArgs>
        TReturnType operator()(TArgs... args) const;
    };
    
    template <typename TCallback, typename TContext, typename TReturnType>
    bool Callback<TCallback, TContext, TReturnType>::IsSet() const
    {
        return this->call != nullptr;
    }

    template <typename TCallback, typename TContext, typename TReturnType>
    void Callback<TCallback, TContext, TReturnType>::SetCallback(TCallback callback, TContext *userdata)
    {
        this->call = callback;
        this->usrdata = userdata;
    }

    template <typename TCallback, typename TContext, typename TReturnType>
    template <typename... TArgs>
    TReturnType Callback<TCallback, TContext, TReturnType>::Invoke(TArgs... args) const
    {
        if (this->call != nullptr)
        {
            return this->call(this->usrdata, args...);
        }
        return TReturnType();
    }

    template <typename TCallback, typename TContext, typename TReturnType>
    template <typename... TArgs>
    TReturnType Callback<TCallback, TContext, TReturnType>::operator()(TArgs... args) const
    {
        return Invoke(args...);
    }
} // namespace libEmbedded

#endif // LIBEMBEDDED_CALLBACK_H
