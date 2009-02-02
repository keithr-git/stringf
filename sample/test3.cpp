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

    length = format::outf(buf, sizeof(buf), "%.*f", 28,
            (double) 1 / (double) 3);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%.*f",
            __DBL_MAX_10_EXP__, __DBL_MIN__);
    printf("%d: %s\n", length, buf);
    return 0;
}
