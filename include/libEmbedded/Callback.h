/**
 * @file Callback.h
 * @author Giel Willemsen
 * @brief Wrapper for a function pointer with a userdata parameter.
 * @version 0.1 2022-02-07 Initial version
 * @version 0.1 2022-03-09 Addition of specific Invoke method.
 * @version 0.1 2022-03-14 Update to include function pointer deconstruction into template arguments for proper type safety
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBEMBEDDED_CALLBACK_H
#define LIBEMBEDDED_CALLBACK_H
#include "libEmbedded/TemplateUtil.h"

namespace libEmbedded
{
    template<typename TRet, typename... TArgs>
    class CallbackBase
    {
    protected:
        using ReturnType = TRet;
        using ContextType = typename libEmbedded::templateUtil::First<TArgs...>::Type;
        using Pointer = TRet(*)(TArgs...);

        static constexpr Pointer CleanCallback = nullptr;

    protected:
        Pointer _callback;
        ContextType _context;

    protected:
        constexpr CallbackBase(Pointer callback, ContextType context) : _callback(callback), _context(context)
        {}

        bool IsSet() const
        {
            return this->_callback != CleanCallback;
        };

        void SetCallback(Pointer callback, ContextType context)
        {
            this->_callback = callback;
            this->_context = context;
        };

        bool operator==(const CallbackBase<TRet, TArgs...> &other) const
        {
            return other._callback == this->_callback && other._context == this->_context;
        };

        bool operator!=(const CallbackBase<TRet, TArgs...> &other) const
        {
            return other._callback != this->_callback || other._context != this->_context;
        };
    };

    template<typename T>
    struct Callback;    

    template<typename TRet, typename TContext, typename... TArgs>
    class Callback<TRet(*)(TContext, TArgs...)> : public CallbackBase<TRet, TContext, TArgs...>
    {
    private:
        using base = CallbackBase<TRet, TContext, TArgs...>;
        using Pointer = typename base::Pointer;
        using ContextType = typename base::ContextType;
    public:
        /**
         * @brief Represents the value that needs to be passed to SetCallbacks to unset the callback.
         * 
         */
        static constexpr Pointer CleanCallback = base::CleanCallback;

    public:
        /**
         * @brief Construct a new callback object that has no callback set.
         * 
         */
        Callback() : CallbackBase<TRet, TContext, TArgs...>(base::CleanCallback, nullptr) {}

        /**
         * @brief Construct a new callback with the given callback handler and userdata instance.
         * 
         * @param callback The callback handler itself.
         * @param context The context instance that is passed to the callback as the first argument.
         */
        Callback(Pointer callback, ContextType context) : CallbackBase<TRet, TContext, TArgs...>(callback, context) {}

        /**
         * @brief Is the callback configured or not?
         * 
         * @return true If the callback is configured.
         * @return false If the callback is left unconfigured.
         */
        bool IsSet() const
        {
            return base::IsSet();
        }

        /**
         * @brief Set the callback handler with context. To clear use the CleanCallback value.
         * 
         * @param callback The callback method to call.
         * @param context The userdata that is passed as the first argument to the callback.
         */
        void SetCallback(Pointer callback, ContextType context)
        {
            base::SetCallback(callback, context);
        }

        /**
         * @brief Invoke the callback, if the callback is set.
         * @details Returns a instance of TRet called with a simple argumentless constructor if 
         * the callback is not set.
         * 
         * @param args The arguments for the callback.
         * @return TRet The return value of the callback. Or the default TRet if no callback is set.
         */
        TRet Invoke(TArgs... args) const
        {
            if (this->IsSet())
            {
                return this->_callback(this->_context, args...);
            }
            return TRet();
        }

        bool operator==(const Callback<TRet(*)(TContext, TArgs...)> &other) const
        {
            return base::operator==(other); //this->_context == other._context && this->_callback == other.callback;
        }

        bool operator!=(const Callback<TRet(*)(TContext, TArgs...)> &other) const
        {
            return base::operator!=(other);
        }
    };

    template<typename TRet, typename TContext>
    class Callback<TRet(*)(TContext)> : public CallbackBase<TRet, TContext>
    {
    private:
        using base = CallbackBase<TRet, TContext>;
        using Pointer = typename base::Pointer;
        using ContextType = typename base::ContextType;
    public:
        /**
         * @brief Represents the value that needs to be passed to SetCallbacks to unset the callback.
         * 
         */
        static constexpr Pointer CleanCallback = base::CleanCallback;

    public:
        /**
         * @brief Construct a new callback object that has no callback set.
         * 
         */
        Callback() : CallbackBase<TRet, TContext>(base::CleanCallback, nullptr) {}

        /**
         * @brief Construct a new callback with the given callback handler and userdata instance.
         * 
         * @param callback The callback handler itself.
         * @param context The context instance that is passed to the callback as the first argument.
         */
        Callback(Pointer callback, ContextType context) : CallbackBase<TRet, TContext>(callback, context) {}

        /**
         * @brief Is the callback configured or not?
         * 
         * @return true If the callback is configured.
         * @return false If the callback is left unconfigured.
         */
        bool IsSet() const
        {
            return base::IsSet();
        }

        /**
         * @brief Set the callback handler with context. To clear use the CleanCallback value.
         * 
         * @param callback The callback method to call.
         * @param context The userdata that is passed as the first argument to the callback.
         */
        void SetCallback(Pointer callback, ContextType context)
        {
            base::SetCallback(callback, context);
        }

        /**
         * @brief Invoke the callback, if the callback is set.
         * @details Returns a instance of TRet called with a simple argumentless constructor if 
         * the callback is not set.
         * 
         * @return TRet The return value of the callback. Or the default TRet if no callback is set.
         */
        TRet Invoke() const
        {
            if (this->IsSet())
            {
                return this->_callback(this->_context);
            }
            return TRet();
        }

        bool operator==(const Callback<TRet(*)(TContext)> &other) const
        {
            return base::operator==(other); //this->_context == other._context && this->_callback == other.callback;
        }

        bool operator!=(const Callback<TRet(*)(TContext)> &other) const
        {
            return base::operator!=(other);
        }
    };

    template<typename TContext>
    class Callback<void(*)(TContext)> : private CallbackBase<void, TContext>
    {
    private:
        using base = CallbackBase<void, TContext>;
        using Pointer = typename base::Pointer;
        using ContextType = typename base::ContextType;
    public:
        /**
         * @brief Represents the value that needs to be passed to SetCallbacks to unset the callback.
         * 
         */
        static constexpr Pointer CleanCallback = base::CleanCallback;

    public:
        /**
         * @brief Construct a new callback object that has no callback set.
         * 
         */
        Callback() : CallbackBase<void, TContext>(base::CleanCallback, nullptr) {}

        /**
         * @brief Construct a new callback with the given callback handler and userdata instance.
         * 
         * @param callback The callback handler itself.
         * @param context The context instance that is passed to the callback as the first argument.
         */
        Callback(Pointer callback, ContextType context) : CallbackBase<void, TContext>(callback, context) {}

        /**
         * @brief Is the callback configured or not?
         * 
         * @return true If the callback is configured.
         * @return false If the callback is left unconfigured.
         */
        bool IsSet() const
        {
            return base::IsSet();
        }

        /**
         * @brief Set the callback handler with context. To clear use the CleanCallback value.
         * 
         * @param callback The callback method to call.
         * @param context The userdata that is passed as the first argument to the callback.
         */
        void SetCallback(Pointer callback, ContextType context)
        {
            base::SetCallback(callback, context);
        }

        /**
         * @brief Invokes the callback, if one is set.
         * 
         */
        void Invoke() const
        {
            if (this->IsSet())
            {
                this->_callback(this->_context);
            }
        }

        bool operator==(const Callback<void (*)(TContext)> &other) const
        {
            return base::operator==(other); //this->_context == other._context && this->_callback == other.callback;
        }

        bool operator!=(const Callback<void (*)(TContext)> &other) const
        {
            return base::operator!=(other);
        }
    };

    template<typename TContext, typename... TArgs>
    class Callback<void (*)(TContext, TArgs...)> : public CallbackBase<void, TContext, TArgs...>
    {
    private:
        using base = CallbackBase<void, TContext, TArgs...>;
        using Pointer = typename base::Pointer;
        using ContextType = typename base::ContextType;
    public:
        /**
         * @brief Represents the value that needs to be passed to SetCallbacks to unset the callback.
         * 
         */
        static constexpr Pointer CleanCallback = base::CleanCallback;

    public:
        /**
         * @brief Construct a new callback object that has no callback set.
         * 
         */
        Callback() : CallbackBase<void, TContext, TArgs...>(base::CleanCallback, nullptr) {}

        /**
         * @brief Construct a new callback with the given callback handler and userdata instance.
         * 
         * @param callback The callback handler itself.
         * @param context The context instance that is passed to the callback as the first argument.
         */
        Callback(Pointer callback, ContextType context) : CallbackBase<void, TContext, TArgs...>(callback, context) {}

        /**
         * @brief Is the callback configured or not?
         * 
         * @return true If the callback is configured.
         * @return false If the callback is left unconfigured.
         */
        bool IsSet() const
        {
            return base::IsSet();
        }

        /**
         * @brief Set the callback handler with context. To clear use the CleanCallback value.
         * 
         * @param callback The callback method to call.
         * @param context The userdata that is passed as the first argument to the callback.
         */
        void SetCallback(Pointer callback, ContextType context)
        {
            base::SetCallback(callback, context);
        }

        /**
         * @brief Invokes the callback with the given arguments, if a callback is set.
         * 
         * @param args The arguments to pass to the callback handler.
         */
        void Invoke(TArgs... args) const
        {
            if (this->IsSet())
            {
                this->_callback(this->_context, args...);
            }
        }

        bool operator==(const Callback<void(*)(TContext, TArgs...)> &other) const
        {
            return base::operator==(other); //this->_context == other._context && this->_callback == other.callback;
        }

        bool operator!=(const Callback<void (*)(TContext, TArgs...)> &other) const
        {
            return base::operator!=(other);
        }
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_CALLBACK_H
