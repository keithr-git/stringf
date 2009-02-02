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
#ifndef __LDBL_DIG__
#define __LDBL_DIG__            18      /* 80-bit extended */
#endif

#define FLOAT_TEST_NAME         LongDouble
#define FLOAT_TEST_TYPE         long double
#define FLOAT_TEST_MAX          __LDBL_MAX__
#define FLOAT_TEST_MIN          __LDBL_MIN__
#define FLOAT_TEST_MAX_DIGITS   __LDBL_DIG__
#define FLOAT_TEST_PREFIX       "L"

#include "float.hpp"
