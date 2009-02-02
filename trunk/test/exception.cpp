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
#include <typeinfo>

#include <stringf/stringf.hpp>

#define BOOST_TEST_MODULE Exception
#include <boost/test/unit_test.hpp>

#define TRY1(EXCEPTION, FORMAT, ...) \
    try { \
        char buf[4096]; \
        format::outf(buf, sizeof(buf), FORMAT, ## __VA_ARGS__); \
        BOOST_ERROR("Expected " #EXCEPTION " exception"); \
    } catch(EXCEPTION& e) { \
    } catch(std::exception& e) { \
        char error[4096]; \
        format::outf(error, sizeof(error), "Unexpected exception(%s): %s", \
                typeid(e).name(), e.what()); \
        BOOST_ERROR(error); \
    }

#define TRY2(EXCEPTION, FORMAT, ...) \
    try { \
        char buf[4096]; \
        format::outf(buf, sizeof(buf), FORMAT, ## __VA_ARGS__); \
        BOOST_ERROR("Expected " #EXCEPTION " exception"); \
    } catch(format::exception::base& e) { \
        if (e.is<EXCEPTION>()) { \
            /* OK */ \
        } else { \
            char error[4096]; \
            format::outf(error, sizeof(error), \
                    "Unexpected format exception(%s): %s", \
                    typeid(e).name(), e.what()); \
            BOOST_ERROR(error); \
        } \
    } catch(std::exception& e) { \
        char error[4096]; \
        format::outf(error, sizeof(error), "Unexpected exception(%s): %s", \
                typeid(e).name(), e.what()); \
        BOOST_ERROR(error); \
    }

BOOST_AUTO_TEST_CASE( Exception1 )
{
    TRY1(format::parse_error, "%*2d", 1, 1);
    TRY2(format::parse_error, "%*2d", 1, 1);
}

BOOST_AUTO_TEST_CASE( Exception2 )
{
    TRY1(format::index_error, "%*2$d", 1, "foo");
    TRY2(format::index_error, "%*2$d", 1, "foo");
}

BOOST_AUTO_TEST_CASE( Exception3 )
{
    TRY1(format::argument_error, "%d");
    TRY2(format::argument_error, "%d");
}
