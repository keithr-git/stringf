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
#ifndef FORMAT_TYPE_SORT_HPP
#define FORMAT_TYPE_SORT_HPP

#include <boost/type_traits/remove_cv.hpp>

namespace format 
{
    namespace detail
    {
        /** A predicate for sorting a list of types.
         *
         * Compares two types and returns true if the first one
         * is "less than" the second.  The goal is to generate
         * the same variant for calls to outf() that pass the
         * same set of types of arguments, regardless of the
         * number or order of the arguments.  This serves several
         * purposes:
         *
         * -   Minimizes the number of different instantiations
         *     of do_format().
         *
         * -   Allows the boost::mpl::unique<> metafunction to
         *     remove duplicate types (it only removes duplicates
         *     if they're adjacent).
         *
         * If two different types appear the same to the
         * type_less metafunction, their order in the list will
         * depend on the order they are passed to outf(), and
         * duplicates may not be removed from the variant's type
         * list.  That means extra instantiations of do_format(),
         * but
         */
        template<typename T1>
        struct sort_order
        {
            BOOST_STATIC_CONSTANT(int, value = 500);
        };

        template<>
        struct sort_order<int>
        {
            BOOST_STATIC_CONSTANT(int, value = 0);
        };

        template<>
        struct sort_order<unsigned int>
        {
            BOOST_STATIC_CONSTANT(int, value = 1);
        };

        template<>
        struct sort_order<long>
        {
            BOOST_STATIC_CONSTANT(int, value = 2);
        };

        template<>
        struct sort_order<unsigned long>
        {
            BOOST_STATIC_CONSTANT(int, value = 3);
        };

        template<>
        struct sort_order<long long>
        {
            BOOST_STATIC_CONSTANT(int, value = 4);
        };

        template<>
        struct sort_order<unsigned long long>
        {
            BOOST_STATIC_CONSTANT(int, value = 5);
        };

        template<>
        struct sort_order<float>
        {
            BOOST_STATIC_CONSTANT(int, value = 6);
        };

        template<>
        struct sort_order<double>
        {
            BOOST_STATIC_CONSTANT(int, value = 7);
        };

        template<>
        struct sort_order<long double>
        {
            BOOST_STATIC_CONSTANT(int, value = 8);
        };

        struct type_less
        {
            template<typename T1, typename T2>
            struct apply_impl :
                ::boost::mpl::bool_<
                  sort_order<T1>::value < sort_order<T2>::value
              >
            {
            };

            template<typename T1, typename T2>
            struct apply : apply_impl<typename boost::remove_cv<T1>::type,
                                        typename boost::remove_cv<T2>::type>
            {
            };
        };

    }; // namespace detail
}; // namespace format

#endif /* FORMAT_TYPE_SORT_HPP */
