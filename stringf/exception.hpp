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
#ifndef FORMAT_EXCEPTION_HPP
#define FORMAT_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace format
{
    namespace exception
    {
        struct PARSE_ERROR      { enum { code = 1 }; };
        struct ARGUMENT_ERROR   { enum { code = 2 }; };
        struct INDEX_ERROR      { enum { code = 3 }; };
        struct FORMAT_ERROR     { enum { code = 4 }; };

        class base : public std::runtime_error
        {
            int             code_;

        public:
            base(int code, const std::string& message)
                : std::runtime_error(message), code_(code)
            { }

            template <typename EXCEPTION>
            inline bool is() const
            {
                return code_ == EXCEPTION::code();
            }
        };

        template <typename EXCEPTION>
        class exception : public base
        {
        public:
            exception(const std::string& message)
                : base(EXCEPTION::code, message)
            { }

            static int code()
            {
                return EXCEPTION::code;
            }
        };
    };

    typedef exception::exception<exception::PARSE_ERROR>        parse_error;
    typedef exception::exception<exception::ARGUMENT_ERROR>     argument_error;
    typedef exception::exception<exception::INDEX_ERROR>        index_error;
    typedef exception::exception<exception::FORMAT_ERROR>       format_error;
};

#endif /* FORMAT_EXCEPTION_HPP */
