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
#ifndef FORMAT_INTEGER_HPP
#define FORMAT_INTEGER_HPP

#include <limits.h>
#include <string.h>

#include <boost/integer.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>

namespace format
{
    namespace detail
    {
        struct integer_type_tag
        { };

        template<typename T>
        struct type_tag<T,
            typename boost::enable_if<boost::is_integral<T> >::type >
        {
            typedef integer_type_tag      type;
        };

        template<typename T>
        struct to_signed
        {
            typedef typename boost::int_t<sizeof(T) * CHAR_BIT>::fast type;
        };

        template<typename T>
        struct to_unsigned
        {
            typedef typename boost::uint_t<sizeof(T) * CHAR_BIT>::fast type;
        };

        template<typename T, typename Enabled = void>
        struct format_type;

        template<typename T>
        struct format_type<T,
            typename boost::enable_if_c<boost::is_signed<T>::value &&
                                sizeof(T) <= sizeof(int)>::type>
        {
            typedef int type;
        };

        template<typename T>
        struct format_type<T,
            typename boost::enable_if_c<boost::is_unsigned<T>::value &&
                                sizeof(T) <= sizeof(int)>::type>
        {
            typedef unsigned int type;
        };

        template<typename T>
        struct format_type<T,
            typename boost::enable_if_c<boost::is_unsigned<T>::value &&
                                sizeof(int) < sizeof(T)>::type>
        {
            typedef long long type;
        };

        template<typename T>
        struct format_type<T,
            typename boost::enable_if_c<boost::is_signed<T>::value &&
                                sizeof(int) < sizeof(T)>::type>
        {
            typedef unsigned long long type;
        };

        template<int Base>
        class integer_formatter
        {
        public:
            integer_formatter(const format_spec&)
            { }

            template<typename T>
            char next_digit(T& num)
            {
                char c = '0' + (num % Base);
                num /= Base;
                return c;
            }
        };

        template<>
        class integer_formatter<16>
        {
            const char*     digits;

        public:
            integer_formatter(const format_spec& fspec)
                : digits((fspec.type == 'X' || fspec.type == 'P') ?
                    "0123456789ABCDEF" : "0123456789abcdef")
            { }

            template<typename T>
            char next_digit(T& num)
            {
                char c = digits[(num % 16)];
                num /= 16;
                return c;
            }
        };

        template<int Base, typename T>
        void format_unsigned(char* const buf, types::size& offset,
                const format_spec& fspec, T num)
        {
            integer_formatter<Base> formatter(fspec);
            unsigned int comma_counter = 0;

            do
            {
                buf[--offset] = formatter.next_digit(num);

                if (offset && fspec.commas && ++comma_counter == 3)
                {
                    buf[--offset] = ',';
                    comma_counter = 0;
                }
            }
            while (num && offset);
        }

        void format_number_post(char * const buf, types::size& offset,
                const format_spec& fspec, types::size num_zeros,
                bool const negative)
        {
            num_zeros = std::min(num_zeros, offset);

            if (num_zeros > 0)
            {
                memset(buf + (offset - num_zeros), '0', num_zeros);
                offset -= num_zeros;
            }

            switch (fspec.type)
            {
                case '@':
                case 'd':
                case 'i':
                    if (negative)
                    {
                        buf[--offset] = '-';
                    }
                    else
                    {
                        if (fspec.plus)
                        {
                            buf[--offset] = '+';
                        }
                        else if (fspec.space)
                        {
                            buf[--offset] = ' ';
                        }
                    }
                    break;

                case 'x':
                    if (fspec.alternate)
                    // Fall through...
                case 'p':
                    {
                        buf[--offset] = 'x';
                        buf[--offset] = '0';
                    }
                    break;

                case 'X':
                    if (fspec.alternate)
                    // Fall through...
                case 'P':
                    {
                        buf[--offset] = 'X';
                        buf[--offset] = '0';
                    }
                    break;

                case 'o':
                    if (fspec.alternate)
                    {
                        buf[--offset] = '0';
                    }
                    break;
            }
        }

        template<typename T>
        bool format_number(char* const buf, types::size& offset,
                const format_spec& fspec, const T num)
        {
            types::size num_zeros = 0;
            types::size orig_offset = offset;
            bool negative = false;

            if (fspec.have_precision)
            {
                num_zeros = fspec.precision;
            }
            else if (fspec.zero && fspec.have_width)
            {
                num_zeros = fspec.width;
            }

            switch (fspec.type)
            {
                case '@':
                case 'd':
                case 'i':
                {
                    typename to_signed<T>::type snum = num;
                    typename to_unsigned<T>::type unum = num;

                    if (snum < 0)
                    {
                        negative = true;
                        unum = -num;
                    }

                    if (num_zeros && !fspec.have_precision &&
                            (negative || fspec.plus || fspec.space))
                    {
                        --num_zeros;
                    }

                    format_unsigned<10>(buf, offset, fspec, unum);
                    break;
                }

                case 'u':
                    format_unsigned<10>(buf, offset, fspec,
                            static_cast<typename to_unsigned<T>::type>(num));
                    break;

                case 'X':
                case 'x':
                case 'p':
                case 'P':
                    format_unsigned<16>(buf, offset, fspec,
                            static_cast<typename to_unsigned<T>::type>(num));
                    break;

                case 'o':
                case 'O':
                    format_unsigned<8>(buf, offset, fspec,
                            static_cast<typename to_unsigned<T>::type>(num));
                    break;

                case 'c':
                    buf[--offset] = num;
                    num_zeros = 0;
                    break;

                default:
                    return false;
                    break;

            }

            format_number_post(buf, offset, fspec,
                    num_zeros - (orig_offset - offset), negative);
            return true;
        }

        template<typename Output, typename T>
        types::size format_value(Output& out, const format_spec& fspec,
                const T& num, integer_type_tag)
        {
            // Big enough for a 128-bit number, plus some.
            char buf[44 + fspec.precision + fspec.width];
            types::size offset = sizeof(buf);
            types::size length;
            
            if (format_number(buf, offset, fspec,
                        static_cast<typename format_type<T>::type>(num)))
            {
                length = write_formatted(out, fspec, buf + offset,
                        sizeof(buf) - offset);
            }
            else
            {
                // Not an integer format - try other types.
                switch (fspec.type)
                {
                    case 'e':
                    case 'E':
                    case 'f':
                    case 'F':
                    case 'g':
                    case 'G':
                        length = format_value(out, fspec, (double) num);
                        break;

                    default:
                        length = unknown_format(out, fspec, num, "integer");
                        break;
                }
            }

            return length;
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_INTEGER_HPP */
