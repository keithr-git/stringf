//
//    Copyright 2008, 2009 Keith Reynolds.
//
//    This file is part of Stringf.
//
//    Stringf is free software: you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation,
//    either version 2.1 of the License, or (at your option) any
//    later version.
//
//    Stringf is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty
//    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//    See the GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General
//    Public License along with Stringf.  If not, see
//    <http://www.gnu.org/licenses/>.
//
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
