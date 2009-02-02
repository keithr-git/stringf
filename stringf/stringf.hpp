#ifndef FORMAT_HPP
#define FORMAT_HPP

#ifdef FORMAT_MAX_ARGS
// Non-standard limits don't work with the preprocessed headers.
# undef  BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
# define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS 1
#else
# define FORMAT_MAX_ARGS                20
#endif

#ifdef FORMAT_MAX_TYPES
// Non-standard limits don't work with the preprocessed headers.
# undef  BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
# define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS 1
#else
# define FORMAT_MAX_TYPES               20
#endif

//
// The current boost implementation limits vectors to 50 elements or
// fewer, but we might as well go higher in case that limit ever changes.
//
#if FORMAT_MAX_ARGS > 100
#error FORMAT_MAX_ARGS too high (max 100)
#elif FORMAT_MAX_ARGS > 90
#define BOOST_MPL_LIMIT_VECTOR_SIZE     100
#elif FORMAT_MAX_ARGS > 80
#define BOOST_MPL_LIMIT_VECTOR_SIZE     90
#elif FORMAT_MAX_ARGS > 70
#define BOOST_MPL_LIMIT_VECTOR_SIZE     80
#elif FORMAT_MAX_ARGS > 60
#define BOOST_MPL_LIMIT_VECTOR_SIZE     70
#elif FORMAT_MAX_ARGS > 50
#define BOOST_MPL_LIMIT_VECTOR_SIZE     60
#elif FORMAT_MAX_ARGS > 40
#define BOOST_MPL_LIMIT_VECTOR_SIZE     50
#elif FORMAT_MAX_ARGS > 30
#define BOOST_MPL_LIMIT_VECTOR_SIZE     40
#elif FORMAT_MAX_ARGS > 20
#define BOOST_MPL_LIMIT_VECTOR_SIZE     30
#elif FORMAT_MAX_ARGS > 10
#define BOOST_MPL_LIMIT_VECTOR_SIZE     20
#else
#define BOOST_MPL_LIMIT_VECTOR_SIZE     10
#endif

//
// The current boost implementation limits vectors to 50 elements or
// fewer, but we might as well go higher in case that limit ever changes.
//
#if FORMAT_MAX_TYPES > 100
#error FORMAT_MAX_TYPES too high (max 100)
#elif FORMAT_MAX_TYPES > 90
#define BOOST_MPL_LIMIT_LIST_SIZE       100
#elif FORMAT_MAX_TYPES > 80
#define BOOST_MPL_LIMIT_LIST_SIZE       90
#elif FORMAT_MAX_TYPES > 70
#define BOOST_MPL_LIMIT_LIST_SIZE       80
#elif FORMAT_MAX_TYPES > 60
#define BOOST_MPL_LIMIT_LIST_SIZE       70
#elif FORMAT_MAX_TYPES > 50
#define BOOST_MPL_LIMIT_LIST_SIZE       60
#elif FORMAT_MAX_TYPES > 40
#define BOOST_MPL_LIMIT_LIST_SIZE       50
#elif FORMAT_MAX_TYPES > 30
#define BOOST_MPL_LIMIT_LIST_SIZE       40
#elif FORMAT_MAX_TYPES > 20
#define BOOST_MPL_LIMIT_LIST_SIZE       30
#elif FORMAT_MAX_TYPES > 10
#define BOOST_MPL_LIMIT_LIST_SIZE       20
#else
#define BOOST_MPL_LIMIT_LIST_SIZE       10
#endif

// #define BOOST_VARIANT_LIMIT_TYPES       FORMAT_MAX_ARGS

#include <stringf/types.hpp>
#include <stringf/exception.hpp>
#include <stringf/format_spec.hpp>
#include <stringf/parse.hpp>
#include <stringf/do_format.hpp>
#include <stringf/output.hpp>
#include <stringf/integer.hpp>
#include <stringf/float.hpp>
#include <stringf/string.hpp>
#include <stringf/pointer.hpp>
#include <stringf/declarations.hpp>
#include <stringf/unknown.hpp>

#endif /* FORMAT_HPP */
