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

#define BOOST_TEST_MODULE Double
#include <boost/test/unit_test.hpp>

#include "test.hpp"

#ifndef FLOAT_TEST_PREFIX
#define FLOAT_TEST_PREFIX       ""
#endif

#define FLOAT_TEST_FORMAT(modifiers, format) \
    "%" modifiers FLOAT_TEST_PREFIX format

static const char *const fp_formats[] = {
    "%-1.5f",   "%1.5f",    "%31.9f",   "%10.5f",   "% 10.5f",  "%+22.9f",
    "%+4.9f",   "%01.3f",   "%3.1f",    "%3.2f",    "%.0f",     "%.1f",
    "%f",       NULL
};

static const double fp_nums[] = {
    -1.5, 134.21, 91340.2, 341.1234, 0203.9, 0.96, 0.996, 0.9996, 1.996,
    4.136, 0
};

BOOST_AUTO_TEST_CASE( Double1 )
{
    TRY_LIMITED(FLOAT_TEST_MAX_DIGITS, FLOAT_TEST_FORMAT("", "f"),
            (FLOAT_TEST_TYPE) FLOAT_TEST_MAX);
    TRY(FLOAT_TEST_FORMAT(".*", "f"), FLOAT_TEST_MAX_DIGITS,
            static_cast<FLOAT_TEST_TYPE>(1) /
                static_cast<FLOAT_TEST_TYPE>(3));
    TRY(FLOAT_TEST_FORMAT("", "f"),
            static_cast<FLOAT_TEST_TYPE>(FLOAT_TEST_MIN));
    TRY(FLOAT_TEST_FORMAT("", "f"), (FLOAT_TEST_TYPE) 1.1);
    TRY(FLOAT_TEST_FORMAT("5", "f"), (FLOAT_TEST_TYPE) 1.0);
    TRY(FLOAT_TEST_FORMAT(".5", "f"), (FLOAT_TEST_TYPE) 1.0);
    TRY(FLOAT_TEST_FORMAT("-5", "f"), (FLOAT_TEST_TYPE) 1.0);
    TRY(FLOAT_TEST_FORMAT("+5", "f"), (FLOAT_TEST_TYPE) 1.0);
    TRY(FLOAT_TEST_FORMAT(" 5", "f"), (FLOAT_TEST_TYPE) 1.0);
    TRY(FLOAT_TEST_FORMAT("05", "f"), (FLOAT_TEST_TYPE) 1.0);
}

BOOST_AUTO_TEST_CASE( Double2 )
{
    TRY(FLOAT_TEST_FORMAT("", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT("5", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT(".5", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT("-5", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT("+5", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT(" 5", "f"), (FLOAT_TEST_TYPE) -1.0);
    TRY(FLOAT_TEST_FORMAT("05", "f"), (FLOAT_TEST_TYPE) -1.0);
}
