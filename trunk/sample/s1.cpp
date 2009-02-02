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

void mycopy(char* const __restrict__ dest, const char* const __restrict__ src)
{
    strcpy(dest, src);
}

void bar(char* const __restrict__ buf, size_t)
{
    mycopy(buf, "foobars");
}

void foo(char* __restrict__ buf, size_t bufsize)
{
    format::outf(buf, bufsize, "%s", "foobars");
}

int
main()
{
    return 0;
}
