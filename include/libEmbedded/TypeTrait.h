/**
 * @file TypeTrait.h
 * @author Giel Willemsen
 * @brief Some reimplementations of the STL type_trait headers.
 * @version 0.1 2022-10-23 Initial version
 * @version 0.2 2022-10-27 If you try to reimplement the std don't depend on the std.  is_member_object_pointer inherited from std::integral_constant
 * @date 2022-10-27
 *
 * @copyright Copyright (c) 2022
 *
 * @details
 *
 * Disclaimer:
 * A lot of this code is based on the code examples provided at cppreference.com.
 * Sure, most are simple enough that I could have worked out my own, but they would
 * have been the same mostly, only I would be much more unsure about how correct
 * they were and it would have taken me much longer than looking at the site and
 * making my own version based on that.
 * And even if they are not 'completely' according to the standard, they are good
 * enough for me.
 *
 * I also avoided the types that would depend too much on compiler specific's or
 * require compiler build-in's. I just want something small, portable, and most of
 * all, useable.
 *
 * Why:
 * This 're-implementation' was added because I also wanted to use this library
 * for platforms like the Arduino (I know, not you 'professional' target but I do
 * hobby). And while Arduino has a standard GCC compiler the standard library is,
 * lacking, to put it mildly. So, to fill in the gap for the features that
 * libEmbedded uses, + some extra things added along the way, this header exists.
 */
#ifndef LIBEMBEDDED_TYPE_TRAIT_H
#define LIBEMBEDDED_TYPE_TRAIT_H
#include <stddef.h>

namespace libEmbedded
{
    // Basics
    template<typename T, T v>
    struct integral_constant
    {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant; // using injected-class-name
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template<typename T, typename U> struct is_same : false_type {};
    template<typename T> struct is_same<T, T> : true_type {};

    // Type properties
    template<typename T> struct is_volatile : false_type {};
    template<typename T> struct is_volatile< volatile T> : true_type {};

    template<typename T> struct is_const : false_type {};
    template<typename T> struct is_const< const T> : true_type {};

    // Const-volatility specifiers
    template<typename T> struct remove_cv { typedef T type; };
    template<typename T> struct remove_cv<const T> { typedef T type; };
    template<typename T> struct remove_cv<volatile T> { typedef T type; };
    template<typename T> struct remove_cv<const volatile T> { typedef T type; };

    template<typename T> struct remove_const { typedef T type; };
    template<typename T> struct remove_const<const T> { typedef T type; };

    template<typename T> struct remove_volatile { typedef T type; };
    template<typename T> struct remove_volatile<volatile T> { typedef T type; };

    template<typename T> struct add_cv { typedef const volatile T type; };
    template<typename T> struct add_const { typedef const T type; };
    template<typename T> struct add_volatile { typedef volatile T type; };

    // Composite type categories
    template<typename T > struct is_member_pointer_helper : false_type {};
    template<typename T, typename U > struct is_member_pointer_helper<T U::*> : true_type {};
    template<typename T > struct is_member_pointer : is_member_pointer_helper<typename remove_cv<T>::type> {};

    // Type categories
    template<typename T> struct is_void : is_same<void, typename remove_cv<T>::type> {};

    template<typename T> struct is_lvalue_reference : false_type {};
    template<typename T> struct is_lvalue_reference<T&> : true_type {};

    template<typename T> struct is_rvalue_reference : false_type {};
    template<typename T> struct is_rvalue_reference<T&&> : true_type {};

    template<typename T> struct is_reference : false_type {};
    template<typename T> struct is_reference<T&> : true_type {};
    template<typename T> struct is_reference<T&&> : true_type {};
    template<typename T> struct is_array : false_type {};
    template<typename T> struct is_array<T[]> : true_type {};
    template<typename T, size_t N> struct is_array<T[N]> : true_type {};

    template<typename T> struct is_function : integral_constant<bool, !is_const<const T>::value && !is_reference<T>::value> {};

    template<typename T> struct is_pointer : false_type {};
    template<typename T> struct is_pointer<T*> : true_type {};
    template<typename T> struct is_pointer<T* const> : true_type {};
    template<typename T> struct is_pointer<T* volatile> : true_type {};
    template<typename T> struct is_pointer<T* const volatile> : true_type {};

    template<typename T > struct is_member_function_pointer_helper : false_type {};
    template<typename T, typename U> struct is_member_function_pointer_helper<T U::*> : is_function<T> {};
    template<typename T > struct is_member_function_pointer : is_member_function_pointer_helper<typename remove_cv<T>::type> {};

    template<typename T> struct is_member_object_pointer : integral_constant<bool, is_member_pointer<T>::value && !is_member_function_pointer<T>::value> {};

    // Property queries
    template< typename T > struct alignment_of : integral_constant<size_t, alignof(T)> {};

    template<typename T> struct rank : public integral_constant<size_t, 0> {};
    template<typename T> struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1> {};
    template<typename T, size_t N> struct rank<T[N]> : public integral_constant<size_t, rank<T>::value + 1> {};

    template<typename T, unsigned N = 0> struct extent : integral_constant<size_t, 0> {};
    template<typename T> struct extent<T[], 0> : integral_constant<size_t, 0> {};
    template<typename T, unsigned N> struct extent<T[], N> : extent<T, N - 1> {};
    template<typename T, size_t I> struct extent<T[I], 0> : integral_constant<size_t, I> {};
    template<typename T, size_t I, unsigned N> struct extent<T[I], N> : extent<T, N - 1> {};

    // References

    template<typename T> struct remove_reference { typedef T type; };
    template<typename T> struct remove_reference<T&> { typedef T type; };
    template<typename T> struct remove_reference<T&&> { typedef T type; };

    // Pointers
    template<typename T> struct remove_pointer { typedef T type; };
    template<typename T> struct remove_pointer<T*> { typedef T type; };
    template<typename T> struct remove_pointer<T* const> { typedef T type; };
    template<typename T> struct remove_pointer<T* volatile> { typedef T type; };
    template<typename T> struct remove_pointer<T* const volatile> { typedef T type; };

    // Miscellaneous transformations

    template<size_t Len, size_t Align>
    struct aligned_storage
    {
        struct type
        {
            alignas(Align) unsigned char data[Len];
        };
    };

    template<bool B, typename T = void> struct enable_if {};
    template<typename T> struct enable_if<true, T> { typedef T type; };

    template<bool B, typename T, typename F> struct conditional { using type = T; };
    template<typename T, typename F> struct conditional<false, T, F> { using type = F; };

} // namespace libEmbedded

#endif // LIBEMBEDDED_TYPE_TRAIT_H
