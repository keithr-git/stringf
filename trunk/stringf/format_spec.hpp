#ifndef FORMAT_FORMAT_SPEC_HPP
#define FORMAT_FORMAT_SPEC_HPP

#include <iosfwd>
#include <iomanip>
#include <sstream>

#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace format
{
    namespace detail
    {
        struct format_spec
        {
            wchar_t                     type;                   // d, s, x, etc.

            union
            {
                struct
                {
                    unsigned short      alternate:1;       // %#
                    unsigned short      zero:1;            // %0
                    unsigned short      left:1;            // %-
                    unsigned short      center:1;          // %=
                    unsigned short      space:1;           // %  (%<space>)
                    unsigned short      plus:1;            // %+
                    unsigned short      commas:1;          // %'
                    unsigned short      have_width:1;      // %NUM
                    unsigned short      width_index:1;     // *NUM$
                    unsigned short      have_precision:1;  // %.NUM
                    unsigned short      precision_index:1; // .*NUM$
                };

                unsigned short          flags;
            };

            types::size                 width;
            types::size                 precision;

            format_spec()
                : flags(0), width(0), precision(0)
            { }
        };

        template<typename _CharT, typename _Traits>
        std::basic_ostream<_CharT, _Traits>&
        operator<<(std::basic_ostream<_CharT, _Traits>& stream,
                const format_spec& fspec)
        {
            if (fspec.have_width)
            {
                stream.width(fspec.width);
            }

            if (fspec.have_precision)
            {
                stream.precision(fspec.precision);
            }

            if (fspec.zero)
            {
                stream.fill('0');
            }
            else
            {
                stream.fill(' ');
            }

            if (fspec.left)
            {
                stream.setf(std::ios::left);
            }

            return stream;
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_FORMAT_SPEC_HPP */
