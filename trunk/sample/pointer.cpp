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
#include <iostream>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using std::string;
using namespace format;

int
main(int, char * const *argv)
{
    int len(0);

    format::outf(std::cout, "%p %s\n", argv[0], argv[0]);
    format::outf(std::cout, "%p\n", (void*) argv);
    format::outf("%p%n\n", argv[0], &len);
    format::outf("%d\n", len);
}
