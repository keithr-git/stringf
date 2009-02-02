#ifndef FORMAT_TYPE_TRAITS_HPP
#define FORMAT_TYPE_TRAITS_HPP

#include <boost/type_traits/remove_cv.hpp>

namespace format 
{
    namespace detail
    {
        namespace type_traits
        {
            template<typename T>
            struct is_character_pointer
            {
                typedef boost::false_type type;
                BOOST_STATIC_CONSTANT(bool, value = false);
            };

            template<>
            struct is_character_pointer<char*>
            {
                typedef boost::true_type type;
                BOOST_STATIC_CONSTANT(bool, value = true);
            };

            template<>
            struct is_character_pointer<wchar_t*>
            {
                typedef boost::true_type type;
                BOOST_STATIC_CONSTANT(bool, value = true);
            };
        }; // namespace type_traits
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_TYPE_TRAITS_HPP */
