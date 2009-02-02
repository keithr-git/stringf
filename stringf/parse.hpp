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
#ifndef FORMAT_PARSE_HPP
#define FORMAT_PARSE_HPP

namespace format
{
    namespace detail
    {
        static inline unsigned long
        strtoul(const char* __restrict__ str,
                const char* __restrict__ * endptr,
                int base)
        {
            return ::strtoul(str, (char**) endptr, base);
        }

        static inline unsigned long
        strtoul(const wchar_t* __restrict__ str,
                const wchar_t* __restrict__ * endptr,
                int base)
        {
            return ::wcstoul(str, (wchar_t**) endptr, base);
        }

        template<typename Char>
        void parse(const Char* __restrict__& format, format_spec& fspec,
                types::size& arg_index, const Char*& prefix,
                types::size& prefix_length)
        {
            types::size length = 0;

            prefix = format;

            while (*format && *format != '%')
            {
                ++length;
                ++format;
            }

            prefix_length = length;

            if (*format == 0)
            {
                fspec.type = 0;
                return;
            }

            ++format;

            if (*format == '%')
            {
                //
                // %% - output a single %.  This is handled by returning
                // now, with just the prefix string, and the prefix length
                // incremented to include the first %.
                ++prefix_length;
                ++format;
                fspec.type = '%';
                return;
            }

            if (isdigit(*format) && *format != '0')
            {
                //
                // Possibly a width, possibly an argument index.
                //
                types::size value = strtoul(format, &format, 10);

                if (*format == '$')
                {
                    ++format;
                    arg_index = value - 1;
                }
                else
                {
                    fspec.width = value;
                    fspec.have_width = true;
                }
            }

            if (!fspec.have_width)
            {
                for (bool done = false; !done; ++format)
                {
                    switch (*format)
                    {
                        case '#':
                            fspec.alternate = true;
                            break;

                        case '0':
                            fspec.zero = true;
                            break;

                        case '-':
                            fspec.left = true;
                            break;

                        case '=':
                            fspec.center = true;
                            break;

                        case '+':
                            fspec.plus = true;
                            break;

                        case ' ':
                            fspec.space = true;
                            break;

                        case '\'':
                            fspec.commas = true;
                            break;

                        default:
                            done = true;
                            --format;
                            break;
                    }
                }

                if (*format == '*')
                {
                    fspec.have_width = true;
                    ++format;

                    if (isdigit(*format))
                    {
                        types::size value = strtoul(format, &format, 10);

                        if (*format == '$')
                        {
                            fspec.width = value - 1;
                            fspec.width_index = true;
                        }
                        else
                        {
                            throw parse_error("Missing '$' after positional "
                                    "width specifier");
                        }
                    }
                    else
                    {
                        fspec.width = arg_index++;
                        fspec.width_index = true;
                    }
                }
                else if (isdigit(*format))
                {
                    fspec.width = strtoul(format, &format, 10);
                    fspec.have_width = true;
                }
            }

            if (*format == '.')
            {
                fspec.have_precision = true;
                ++format;

                if (*format == '*')
                {
                    ++format;

                    if (isdigit(*format))
                    {
                        types::size value = strtoul(format, &format, 10);

                        if (*format == '$')
                        {
                            fspec.precision = value - 1;
                            fspec.precision_index = true;
                        }
                        else
                        {
                            throw parse_error("Missing '$' after positional "
                                    "precision specifier");
                        }
                    }
                    else
                    {
                        fspec.precision = arg_index++;
                        fspec.precision_index = true;
                    }
                }
                else
                {
                    fspec.precision = strtoul(format, &format, 10);
                }
            }

            //
            // Skip length modifiers.
            //
            switch (*format)
            {
                case 'h':
                case 'l':
                    // Check for %ll and %hh.
                    if (format[1] == *format)
                    {
                        ++format;
                    }

                // Fall through ...
                case 'j':
                case 'L':
                case 't':
                case 'z':
                    ++format;
                    break;
            }

            fspec.type = *format;

            if (*format)
            {
                ++format;
            }
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_PARSE_HPP */
