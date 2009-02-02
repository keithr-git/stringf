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
#ifndef FORMAT_OUTPUT_HPP
#define FORMAT_OUTPUT_HPP

#include <algorithm>
#include <iterator>

#include <boost/concept_check.hpp>

namespace format
{
    namespace detail
    {
        template<typename Char>
        class output_base
        {
        public:
            typedef Char                char_type;

            BOOST_STATIC_CONSTANT(bool, supported = true);
        };

        template<typename T>
        class output;

        template<typename Char>
        class output<Char*> : public output_base<Char>
        {
            const Char* const           start_;
            Char*                       current_;
            const Char*                 end_;
            types::size                 total_;

            types::size remaining() const
            {
                return end_ - current_;
            }

            types::size limit_length(types::size length) const
            {
                return std::min(length, remaining());
            }

        public:
            output(Char* data, types::size size)
                : start_(data), current_(data), end_(data + size - 1),
                  total_(0)
            { }

            ~output()
            {
                // NUL-terminate the string.
                *current_ = 0;
            }

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
                    if (current_ != end_)
                    {
                        *current_++ = *data;
                    }

                    ++length;
                    ++data;
                }

                total_ += length;
                return length;
            }

            template<typename Iterator>
            types::size write(Iterator start, const Iterator end)
            {
                types::size length(0);

                while (start != end)
                {
                    if (current_ != end_)
                    {
                        *current_++ = *start;
                    }

                    ++length;
                    ++start;
                }

                total_ += length;
                return length;
            }

            template<typename Iterator>
            void write(Iterator data, types::size length)
            {
                types::size limit = limit_length(length);

                for (types::size i = 0; i < limit; ++i)
                {
                    *current_++ = *data++;
                }

                total_ += length;
            }

            void write(types::size count, Char c)
            {
                types::size limit = limit_length(count);

                while (limit--)
                {
                    *current_++ = c;
                }

                total_ += count;
            }
        };

        template<typename CharT_, typename Traits_, typename Alloc_>
        class output< std::basic_string<CharT_, Traits_, Alloc_> >
            : public output_base<CharT_>
        {
            std::basic_string<CharT_, Traits_, Alloc_>& string_;

        public:
            output(std::basic_string<CharT_, Traits_, Alloc_>& string)
                : string_(string)
            {
                string_.clear();
            }

            types::size total() const
            {
                return string_.size();
            }

            types::size write(const CharT_* data)
            {
                types::size start_length = string_.size();

                string_.append(data);
                return string_.size() - start_length;
            }

            template<typename OtherChar>
            types::size write(const OtherChar* data)
            {
                types::size start_length = string_.size();

                while (*data)
                {
                    string_.append(1, *data++);
                }

                return string_.size() - start_length;
            }

            template<typename Iterator>
            void write(Iterator data, types::size length)
            {
                for (types::size i = 0; i < length; ++i)
                {
                    string_.append(1, *data++);
                }
            }

            template<typename Iterator_>
            void write(Iterator_ start, Iterator_ end)
            {
                string_.append(start, end);
            }

            void write(const CharT_* data, types::size length)
            {
                string_.append(data, length);
            }

            void write(types::size count, CharT_ c)
            {
                string_.append(count, c);
            }
        };

        template<typename Output_, typename Iterator_>
        types::size write_formatted(Output_& out, const format_spec& fspec,
                Iterator_ start, types::size length)
        {
            using namespace boost;
            types::size spaces = 0;

            if (fspec.have_width && length < fspec.width)
            {
                spaces = fspec.width - length;
            }

            if (spaces && !fspec.left)
            {
                out.write((fspec.center) ? spaces / 2 : spaces, ' ');
            }

            out.write(start, length);

            if (spaces && (fspec.left || fspec.center))
            {
                out.write((fspec.center) ? (spaces + 1) / 2 : spaces, ' ');
            }

            return length + spaces;
        }

        template<typename Output, typename Char>
        types::size write_formatted(Output& out, const format_spec& fspec,
                const Char* data)
        {
            if (fspec.have_width)
            {
                //
                // There's a width specifier, so we have to go through the
                // string twice: once to count the length, and again to
                // actually output it.
                //
                types::size length(0);
                const Char* cp = data;


                while (*cp++)
                {
                    ++length;
                }

                return write_formatted(out, fspec, data, length);
            }
            else
            {
                return out.write(data);
            }
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_OUTPUT_HPP */
