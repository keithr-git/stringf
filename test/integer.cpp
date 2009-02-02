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

#define BOOST_TEST_MODULE Integer
#include <boost/test/unit_test.hpp>

#include "test.hpp"

BOOST_AUTO_TEST_CASE( Integer1 )
{
    TRY("%d", 1);
    TRY("%5d", 1);
    TRY("%.5d", 1);
    TRY("%-5d", 1);
    TRY("%+5d", 1);
    TRY("% 5d", 1);
    TRY("%05d", 1);
}

BOOST_AUTO_TEST_CASE( Integer2 )
{
    TRY("%d", -1);
    TRY("%5d", -1);
    TRY("%.5d", -1);
    TRY("%-5d", -1);
    TRY("%+5d", -1);
    TRY("% 5d", -1);
    TRY("%05d", -1);
}
