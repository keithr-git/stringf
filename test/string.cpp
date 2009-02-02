#include <stringf/stringf.hpp>

#define BOOST_TEST_MODULE Integer
#include <boost/test/unit_test.hpp>

#include "test.hpp"

BOOST_AUTO_TEST_CASE( string )
{
    TRY("%s", "foo");
}
