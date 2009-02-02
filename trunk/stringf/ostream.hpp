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
#ifndef FORMAT_OSTREAM_HPP
#define FORMAT_OSTREAM_HPP

#include <iostream>

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor.hpp>

//
// Calling outf("format", ...) writes to cout or wcout, depending
// on the type of the format string (char* or wchar_t*).  The
// declarations make sure that the first parameter points to a
// const value, to prevent matching calls like:
//
// outf(buf, "format", ...);
//
// A call like that (with parameters like sprintf) should lead to
// a compiler error, since the size of the buffer is not known.
//
#define FORMAT_OSTREAM_FUNC(z, n, unused) \
    template<typename Char BOOST_PP_COMMA_IF(n) \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename T)> \
    typename boost::enable_if_c<(boost::is_const<Char>::value && \
            sizeof(Char) == sizeof(char)), types::size>::type \
    outf(Char* __restrict__ format \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, T, const& arg)) \
    { \
        detail::output<std::ostream> out(std::cout); \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    } \
    template<typename Char BOOST_PP_COMMA_IF(n) \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename T)> \
    typename boost::enable_if_c<(boost::is_const<Char>::value && \
            sizeof(Char) == sizeof(wchar_t)), types::size>::type \
    outf(Char* __restrict__ format \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, T, const& arg)) \
    { \
        detail::output<std::wostream> out(std::wcout); \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    }

namespace format
{
    namespace detail
    {
        template<typename Char, typename CharTraits>
        class output< std::basic_ostream<Char, CharTraits> >
            : public output_base<Char>
        {
            std::basic_ostream<Char, CharTraits>&       stream_;
            types::size                                 total_;

        public:
            output(std::basic_ostream<Char, CharTraits>& stream)
                : stream_(stream), total_(0)
            { }


            types::size total() const
            {
                return total_;
            }

            template<typename OtherChar>
            types::size write(const OtherChar* data)
            {
                types::size length(0);

                while (*data)
                {
                    stream_.put(*data++);
                    ++length;
                }

                total_ += length;
                return length;
            }

            template<typename Iterator_>
            types::size write(Iterator_ start, Iterator_ end)
            {
                types::size length(0);

                while (start != end)
                {
                    stream_.put(*start++);
                    ++length;
                }

                total_ += length;
                return length;
            }

            void write(Char* data, types::size length)
            {
                stream_.write(data, length);
                total_ += length;
            }

            template<typename Iterator>
            void write(Iterator data, types::size length)
            {
                for (types::size i = 0; i < length; ++i)
                {
                    stream_.put(*data++);
                }

                total_ += length;
            }

            void write(types::size count, char c)
            {
                while (count--)
                {
                    stream_.put(c);
                }

                total_ += count;
            }
        };
    }; // namespace detail

    BOOST_PP_REPEAT(BOOST_PP_ADD(FORMAT_MAX_ARGS, 1), FORMAT_OSTREAM_FUNC, 0)
}; // namespace format

#undef FORMAT_OSTREAM_FUNC

#endif /* FORMAT_OSTREAM_HPP */
