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
#ifndef FORMAT_STRING_HPP
#define FORMAT_STRING_HPP

#include <stringf/type_traits.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/utility/enable_if.hpp>

namespace format
{
    namespace detail
    {
        struct cstring_type_tag
        { };

        template<>
        struct type_tag<char*>
        {
            typedef cstring_type_tag    type;
        };

        template<>
        struct type_tag<wchar_t*>
        {
            typedef cstring_type_tag    type;
        };

        template<typename Output, typename Char>
        types::size format_value(Output& out, const format_spec& fspec,
                Char* const& value, cstring_type_tag)
        {
            switch (fspec.type)
            {
                case '@':
                case 's':
                case 'S':
                    return write_formatted(out, fspec, value);
                    break;

                case 'p':
                    return format_value(out, fspec, (void*) value);
                    break;

                default:
                    return unknown_format(out, fspec, value, "C string");
                    break;
            }
        }

        template<typename Output, typename Char, typename Traits,
            typename Alloc>
        types::size format_value(Output& out, const format_spec& fspec,
                const std::basic_string<Char, Traits, Alloc>& s)
        {
            switch (fspec.type)
            {
                case '@':
                case 's':
                case 'S':
                    return write_formatted(out, fspec, s.begin(), s.size());
                    break;

                default:
                    return unknown_format(out, fspec, s, "C++ string");
                    break;
            }
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_STRING_HPP */
