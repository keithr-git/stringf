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
#include <iostream>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

int
main()
{
    char buf[4096];

    try
    {
        format::outf(buf, sizeof(buf), "%z", 5);
    }
    catch (format::parse_error& e)
    {
        format::outf(std::cerr, "parse error: %s\n", e.what());
    }
    catch (format::exception::base& e)
    {
        if (e.is<format::argument_error>())
        {
            format::outf(std::cerr, "argument error: %s\n", e.what());
        }
        else
        {
            format::outf(std::cerr, "format error: %s\n", e.what());
        }
    }
}
