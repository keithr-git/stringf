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
#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

int
main()
{
    char buf[1024];
    int length;
    // short i = 1;
    // int j = 2;
    // long k = 3;
    unsigned int l = 4;
    const unsigned int L = 42;
    const char* foo = "foo";
    const char* const baz = "baz";

    // length = format::outf(buf, sizeof(buf), "%d %d %d %d", i, j, k, l);
    // format::outf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%s %d", foo, l);
    format::outf("%d: %s\n", length, buf);
    format::outf(L"%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %s", l, "bar");
    format::outf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %s %d %d %s %s", l, "bar", l, L, foo, baz);
    format::outf("%d: %s\n", length, buf);
    // length = format::outf(buf, "%d", l);
    // format::outf("%d: %s\n", length, buf);
    // length = format::outf(buf, sizeof(buf), "%s %s", "foo", "bar");
    // format::outf("%d: %s\n", length, buf);
    // length = format::outf(buf, sizeof(buf), "%s", foo);
    return 0;
}
