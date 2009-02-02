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

typedef unsigned int    i1;
typedef int    i2;
typedef unsigned int    i3;
typedef i2              i4;

int
main()
{
    // unsigned int i(0);
    i1 i1(1);
    i2 i2(2);
    // i3 i3(3);
    // i4 i4(4);
    // size_t size(5);

    format::outf("%d %d\n", i1, i2);
    format::outf("%d %d\n", i2, i1);
    // format::outf("%d\n", i);
    // format::outf("%d %d\n", i, i1);
    // format::outf("%d %d %d\n", i, i1, i2);
    // format::outf("%d %d %d %d\n", i, i1, i2, i3);
    // format::outf("%d %d %d %d %d\n", i, i1, i2, i3, i4);
    // format::outf("%d %d %d %d %d %d\n", i, i1, i2, i3, i4, size);
}
