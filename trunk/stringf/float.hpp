#ifndef FORMAT_FLOAT_HPP
#define FORMAT_FLOAT_HPP

#include <iosfwd>
#include <iomanip>
#include <sstream>

#include <float.h>
#include <math.h>

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>

#ifndef DBL_MAX_10_EXP
#define DBL_MAX_10_EXP          308
#endif

#ifndef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP         4932
#endif

namespace format
{
    namespace detail
    {
        struct float_type_tag
        { };

        template<typename T>
        struct type_tag<T,
            typename boost::enable_if<boost::is_floating_point<T> >::type >
        {
            typedef float_type_tag      type;
        };

        namespace floating
        {
            template<typename T, typename Enabled = void>
            struct format_type;

            template<typename T>
            struct format_type<T,
                typename boost::enable_if_c<boost::is_floating_point<T>::value
                    && sizeof(T) <= sizeof(double)>::type>
            {
                typedef double              type;
            };

            template<typename T>
            struct format_type<T,
                typename boost::enable_if_c<boost::is_floating_point<T>::value
                    && sizeof(double) < sizeof(T)>::type>
            {
                typedef long double         type;
            };

            static int get_precision(const format_spec& fspec)
            {
                if (fspec.have_precision)
                {
                    return fspec.precision;
                }
                else
                {
                    return 6;
                }
            }

            double floor(double const num)
            {
                return ::floor(num);
            }

            long double floor(long double const num)
            {
                return ::floorl(num);
            }

            double pow(double num, double exp)
            {
                return ::pow(num, exp);
            }

            long double pow(long double num, long double exp)
            {
                return ::powl(num, exp);
            }

            double fmod(double num, double exp)
            {
                return ::fmod(num, exp);
            }

            long double fmod(long double num, long double exp)
            {
                return ::fmodl(num, exp);
            }

            template<int Base, typename T>
            static void format_number(char* const buf, types::size& offset,
                    const format_spec& fspec, T num, int precision)
            {
                unsigned int comma_counter = 0;
                const char* digits =
                    (fspec.type == 'X') ? "0123456789ABCDEF"
                                        : "0123456789abcdef";

                while ((precision-- > 0 || num >= 1.0) && offset > 0)
                {
                    T newnum = num / Base;
                    // int digit = num - (floor(newnum) * Base);
                    int digit = fmod(num, Base);

                    buf[--offset] = digits[digit];

                    if (Base == 10 && offset && fspec.commas &&
                            ++comma_counter == 3)
                    {
                        buf[--offset] = ',';
                        comma_counter = 0;
                    }

                    num = newnum;
                }
            }

            template<typename T>
            void format_f(char* const buf, types::size& offset,
                    const format_spec& fspec, T const num)
            {
                int const precision = get_precision(fspec);
                T const integer = floor(num);

                if (precision)
                {
                    T const fraction = num - integer;
                    format_spec frac_fspec;

                    format_number<10>(buf, offset, frac_fspec,
                            fraction * pow(static_cast<T>(10), precision),
                                precision);

                    if (offset)
                    {
                        buf[--offset] = '.';
                    }
                }

                format_number<10>(buf, offset, fspec, integer, 1);
            }

            int ilog10(double const num)
            {
                return logb(num) / 3.3219280948873623478;
            }

            int ilog10(long double const num)
            {
                return logbl(num) / 3.3219280948873623478;
            }

            template<typename T>
            void format_e(char* const buf, types::size& offset,
                    const format_spec& fspec, T num, int exponent,
                    bool const upper)
            {
                bool negative;
                T const normalized = num /
                    pow(static_cast<T>(10.0), static_cast<T>(exponent));

                if (exponent < 0)
                {
                    negative = true;
                    exponent = -exponent;
                }
                else
                {
                    negative = false;
                }

                format_unsigned<10>(buf, offset, fspec, exponent);

                if (offset == 0)
                {
                    return;
                }

                if (exponent < 10)
                {
                    buf[--offset] = '0';

                    if (offset == 0)
                    {
                        return;
                    }
                }

                if (negative)
                {
                    buf[--offset] = '-';
                }
                else
                {
                    buf[--offset] = '+';
                }

                if (offset == 0)
                {
                    return;
                }

                if (upper)
                {
                    buf[--offset] = 'E';
                }
                else
                {
                    buf[--offset] = 'e';
                }

                if (offset == 0)
                {
                    return;
                }

                format_f(buf, offset, fspec, normalized);
            }

            template<typename T>
            bool check_finite(char* const buf, types::size& offset,
                    T const num, bool const upper)
            {
                if (isfinite(num))
                {
                    return true;
                }
                else
                {
                    offset = (offset > 3) ? offset - 3 : 0;

                    if (isinf(num))
                    {
                        if (upper)
                        {
                            memcpy(buf + offset, "INF", 3);
                        }
                        else
                        {
                            memcpy(buf + offset, "inf", 3);
                        }
                    }
                    else // NAN
                    {
                        if (upper)
                        {
                            memcpy(buf + offset, "NAN", 3);
                        }
                        else
                        {
                            memcpy(buf + offset, "nan", 3);
                        }
                    }

                    return false;
                }
            }

            template<typename T>
            bool format_float(char* const buf, types::size& offset,
                    const format_spec& fspec, T num)
            {
                bool negative = signbit(num);
                bool upper = false;

                if (negative)
                {
                    num = -num;
                }

                switch (fspec.type)
                {
                    case 'E':
                        upper = true;
                        // Fall through...
                    case 'e':
                        if (check_finite(buf, offset, num, upper))
                        {
                            format_e(buf, offset, fspec, num,
                                    ilog10(num), upper);
                        }
                        break;

                    case 'F':
                        upper = true;
                        // Fall through...
                    case 'f':
                        if (check_finite(buf, offset, num, upper))
                        {
                            format_f(buf, offset, fspec, num);
                        }
                        break;

                    case 'G':
                        // XXX This does the wrong thing with the precision.
                        upper = true;
                        // Fall through...
                    case 'g':
                        if (check_finite(buf, offset, num, upper))
                        {
                            int exponent = ilog10(num);

                            if (exponent < -4
                                    || exponent >= get_precision(fspec))
                            {
                                format_e(buf, offset, fspec, num,
                                        ilog10(num), upper);
                            }
                            else
                            {
                                format_f(buf, offset, fspec, num);
                            }
                        }
                        break;

                    default:
                        return false;
                }

                if (offset)
                {
                    if (negative)
                    {
                        buf[--offset] = '-';
                    }
                    else
                    {
                        if (fspec.plus)
                        {
                            buf[--offset] = '+';
                        }
                        else if (fspec.space)
                        {
                            buf[--offset] = ' ';
                        }
                    }
                }

                return true;
            }

        }; // namespace float

        template<typename Output, typename T>
        types::size format_value(Output& out, const format_spec& fspec,
                const T num, float_type_tag)
        {
            types::size max_int_digits =
                (sizeof(T) > sizeof(double)) ? LDBL_MAX_10_EXP
                                             : DBL_MAX_10_EXP;
            // Space for the period and e+NNNN.
            char buf[std::max(max_int_digits, fspec.width) +
                    fspec.precision + 8];
            types::size offset = sizeof(buf);

            if (floating::format_float(buf, offset, fspec,
                    static_cast<typename floating::format_type<T>::type>(num)))
            {
                return write_formatted(out, fspec, buf + offset,
                        sizeof(buf) - offset);
            }
            else
            {
                return unknown_format(out, fspec, num, "floating point");
            }
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_FLOAT_HPP */
