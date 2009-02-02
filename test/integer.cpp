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
