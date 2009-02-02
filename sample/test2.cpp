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
    double d = 1042.0371;
    int length;
    short s = -1;
    unsigned short us = 1;
    int i = -2;
    int ui = 2;
    long l = -3;
    unsigned long ul = 3;

    length = format::outf(buf, sizeof(buf), "%d %f", i, d);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%+f %d", d, i);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %u %d %u %d %u %e", s, us, i, ui, l, ul, d);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %u %d %u %d %u %'f", l, ul, i, ui, s, us, d);
    printf("%d: %s\n", length, buf);
    return 0;
}
