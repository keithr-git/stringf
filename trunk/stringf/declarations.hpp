#ifndef FORMAT_DECLARATIONS_HPP
#define FORMAT_DECLARATIONS_HPP

#include <boost/call_traits.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/variant.hpp>

#include <boost/preprocessor.hpp>

#include <stringf/type_sort.hpp>

namespace format
{
    namespace detail
    {
#define FORMAT_EXPAND(...)      __VA_ARGS__

#define FORMAT_TYPE(z, n, unused) \
    BOOST_PP_COMMA_IF(n) typename boost::call_traits<T ## n>::param_type

#define FORMAT_DETAIL_FUNC(z, n, unused) \
        template<typename Dest \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
        types::size do_outf(detail::output<Dest>& out, \
                const typename detail::output<Dest>::char_type* \
                    __restrict__ format \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, T, arg)) \
        { \
            using namespace ::boost::mpl; \
            BOOST_PP_EXPAND(FORMAT_EXPAND BOOST_PP_IF(n, \
                (typedef vector ## n<BOOST_PP_REPEAT_ ## z(n, \
                            FORMAT_TYPE, 0)> \
                        template_types), \
                (typedef vector1<int> template_types))); \
            typedef typename sort< template_types, detail::type_less, \
                    front_inserter< vector0<> > >::type sorted_types; \
            typedef typename unique< sorted_types, boost::is_same<_1, _2>, \
                    front_inserter< vector0<> > >::type unique_types; \
            typedef boost::make_variant_over<typename unique_types::type> \
                    variant; \
            typename variant::type args[n] = \
                    { BOOST_PP_ENUM_PARAMS_Z(z, n, arg) }; \
            return do_format(out, format, args, n); \
        }

        BOOST_PP_REPEAT(BOOST_PP_ADD(FORMAT_MAX_ARGS, 1), FORMAT_DETAIL_FUNC, 0)

#undef FORMAT_EXPAND
#undef FORMAT_TYPE
#undef FORMAT_DETAIL_FUNC

    }; // namespace detail

#define FORMAT_FUNCS(z, n, unused) \
    template<typename Dest, typename Char \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
    types::size outf(detail::output<Dest>& out, \
            const Char* __restrict__ format \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, const T, & arg)) \
    { \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    } \
    template<typename Dest, typename Char \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
    typename boost::enable_if_c<detail::output<Dest>::supported, \
                types::size>::type \
    outf(Dest& dest, const Char* __restrict__ format \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, const T, & arg)) \
    { \
        detail::output<Dest> out(dest); \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    } \
    template<typename Char \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
    types::size outf(Char* buf, types::size bufsize, \
            const Char* __restrict__ format \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, const T, & arg)) \
    { \
        detail::output<Char*> out(buf, bufsize); \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    } \
    template<typename Char \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
    std::basic_string<Char> stringf(const Char* __restrict__ format \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, const T, & arg)) \
    { \
        std::basic_string<Char> s; \
        outf(s, format BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
        return s; \
    }

    BOOST_PP_REPEAT(BOOST_PP_ADD(FORMAT_MAX_ARGS, 1), FORMAT_FUNCS, 0)

#undef FORMAT_FUNCS

}; // namespace format

#undef FORMAT_DETAIL_FUNC
#undef FORMAT_FUNC

#endif /* FORMAT_DECLARATIONS_HPP */
