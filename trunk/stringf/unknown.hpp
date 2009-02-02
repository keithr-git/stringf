#ifndef FORMAT_UNKNOWN_HPP
#define FORMAT_UNKNOWN_HPP

#include <iosfwd>
#include <iomanip>
#include <sstream>

#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace format
{
    namespace detail
    {
        struct generic_unknown_format_tag
        { };

        template<typename T, typename Enabled = void>
        struct unknown_format_tag
        {
            typedef generic_unknown_format_tag  type;
        };

        __attribute__((noreturn))
        void unknown_format_error(const format_spec& fspec,
                const char* const label)
        {
            throw format_error(stringf("Unknown format specifier %%%c "
                        "for %s", fspec.type, label));
        }

        template<typename Output, typename T>
        types::size unknown_format(Output&, const format_spec& fspec,
                const T&, const char* const label, generic_unknown_format_tag)
        {
            unknown_format_error(fspec, label);
        }

        template<typename Output, typename T>
        types::size unknown_format(Output& out, const format_spec& fspec,
                const T& value, const char* const label)
        {
            typename unknown_format_tag<typename basic_type<T>::type>::type tag;

            return unknown_format(out, fspec, value, label, tag);
        }

        template<typename Output, typename T>
        types::size format_value(Output& out, const format_spec& fspec,
                const T& value, unknown_type_tag)
        {
            typedef std::basic_stringstream<typename Output::char_type> stream;
            stream s;

            s << fspec;
            s << value;
            return out.write(s.str().begin(), s.str().end());
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_UNKNOWN_HPP */
