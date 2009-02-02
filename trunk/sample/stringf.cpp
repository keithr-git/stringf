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
#include <string>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using format::stringf;
using format::outf;

int
main()
{
    std::string s;
    // short i = 1;
    // int j = 2;
    // long k = 3;
    unsigned int l = 4;
    const unsigned int L = 42;
    const char* foo = "foo";
    const char* const baz = "baz";

    // s = stringf("%d %d %d %d", i, j, k, l);
    // outf("%d: %s\n", s.size(), s.c_str());
    s = stringf("%s %d", foo, l);
    outf("%d: %s\n", s.size(), s.c_str());
    outf(L"%d: %s\n", s.size(), s.c_str());
    s = stringf("%d %s", l, "bar");
    outf("%d: %s\n", s.size(), s.c_str());
    s = stringf("%d %s %d %d %s %s", l, "bar", l, L, foo, baz);
    outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf(buf, "%d", l);
    // outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf("%s %s", "foo", "bar");
    // outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf("%s", foo);
    return 0;
}
