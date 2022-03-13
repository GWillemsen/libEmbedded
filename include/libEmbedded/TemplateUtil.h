/**
 * @file TemplateUtil.h
 * @author Giel Willemsen
 * @brief Some helper types for dealing with Templates
 * @version 0.1
 * @date 2022-03-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LIBEMBEDDED_TEMPLATE_UTIL
#define LIBEMBEDDED_TEMPLATE_UTIL

namespace libEmbedded
{
    namespace templateUtil
    {
        /**
         * @brief Retrieve the first type from the template list.
         * 
         */
        template<typename T1, typename ...T>
        struct First
        {
            /**
             * @brief The type itself.
             * 
             */
            using Type = T1;
        };

        /**
         * @brief Retrieve the last type in the template list.
         * 
         */
        template<class T1, class ...T>
        struct Last
        {
            /**
             * @brief The type itself.
             * 
             */
            using Type = typename Last<T...>::Type;
        };

        /**
         * @brief Retrieve the last type in the template list.
         * 
         */
        template<class T1>
        struct Last<T1>
        {
            /**
             * @brief The type itself.
             * 
             */
            using Type = T1;
        };
    } // namespace templateUtil
    
} // namespace libEmbedded

#endif // LIBEMBEDDED_TEMPLATE_UTIL
