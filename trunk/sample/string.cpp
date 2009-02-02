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
#include <string>
#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using std::string;
using namespace format;

int
main(int, char * const *)
{
    string s;
    int length;
    // short i = 1;
    // int j = 2;
    // long k = 3;
    unsigned int l = 4;
    // const char* foo = "foo";
    string baz("baz");

    // length = format::outf(s, "%d %d %d %d", i, j, k, l);
    // format::outf(std::cout, "%d: %s\n", length, buf);
    // length = format::outf(s, "%s %d", foo, l);
    // format::outf(std::cout, "%d: %s\n", length, s.c_str());
    length = format::outf(s, "%d %s", l, "bar");
    format::outf(std::cout, "%@: %@\n", length, s);
    length = format::outf(s, "%d %s", l, baz);
    format::outf(std::cout, "%@: %@\n", length, s);
    length = format::outf(s, "%s %s", "foo", "bar");
    format::outf(std::cout, "%@: %@\n", length, s);
    return 0;
}
