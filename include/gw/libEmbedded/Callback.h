/**
 * @file Callback.h
 * @author Giel Willemsen
 * @brief Wrapper for a function pointer with a userdata parameter.
 * @version 0.1 2022-02-07
 * @date 2022-02-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef GW_LIBEMBEDDED_CALLBACK_H
#define GW_LIBEMBEDDED_CALLBACK_H

namespace gw
{
    namespace libEmbedded
    {
        /**
         * @brief A wrapper class for a function pointer with a optional userdata pointer.
         *
         * @tparam TCallback The function pointer for this callback.
         */
        template <typename TCallback, typename TReturnType = void>
        class Callback
        {
        private:
            TCallback call;
            void *usrdata;

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
            constexpr Callback(TCallback callback, void *userdata) : call(callback), usrdata(userdata) {}

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
            void SetCallback(TCallback callback, void *userdata = nullptr);

            /**
             * @brief Invoke the callback itself.
             *
             * @tparam TArgs The type of the arguments for the callback.
             * @param args The arguments for the callback (excluding the userdata).
             */
            template <typename... TArgs>
            TReturnType operator()(TArgs... args) const;
        };
        
        template <typename TCallback, typename TReturnType>
        bool Callback<TCallback, TReturnType>::IsSet() const
        {
            return this->call != nullptr;
        }

        template <typename TCallback, typename TReturnType>
        void Callback<TCallback, TReturnType>::SetCallback(TCallback callback, void *userdata)
        {
            this->call = callback;
            this->usrdata = userdata;
        }

        template <typename TCallback, typename TReturnType>
        template <typename... TArgs>
        TReturnType Callback<TCallback, TReturnType>::operator()(TArgs... args) const
        {
            if (this->call != nullptr)
            {
                return this->call(this->userdata, args...);
            }
            return TReturnType();
        }
    } // namespace libEmbedded
} // namespace gw

#endif // GW_LIBEMBEDDED_CALLBACK_H
