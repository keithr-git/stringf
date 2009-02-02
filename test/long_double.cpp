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
