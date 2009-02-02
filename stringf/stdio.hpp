#ifndef FORMAT_STDIO_HPP
#define FORMAT_STDIO_HPP

#include <stdio.h>

//
// Calling outf("format", ...) writes to cout or wcout, depending
// on the type of the format string (char* or wchar_t*).  The
// declarations make sure that the first parameter points to a
// const value, to prevent matching calls like:
//
// outf(buf, "format", ...);
//
// A call like that (with parameters like sprintf) should lead to
// a compiler error, since the size of the buffer is not known.
//
#define FORMAT_STDIO_FUNC(z, n, unused) \
    template<typename Char \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename T)> \
    types::size outf(FILE* dest, const Char* __restrict__ format \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, const T, & arg)) \
    { \
        detail::output<FILE*> out(dest); \
        return detail::do_outf(out, format \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, arg)); \
    } \

namespace format
{
    namespace detail
    {
        template<>
        class output<std::FILE*> : public output_base<char>
        {
            std::FILE*                  fp_;

            types::size                      total_;

        public:
            output(std::FILE* fp)
                : fp_(fp), total_(0)
            { }

            types::size total() const
            {
                if (ferror(fp_))
                {
                    return -1;
                }
                else
                {
                    return total_;
                }
            }

            types::size write(const char* data)
            {
                types::size length;

                while (*data)
                {
                    fputc(*data++, fp_);
                    ++length;
                }

                total_ += length;
                return length;
            }

            template<typename Iterator>
            types::size write(Iterator i, const Iterator end)
            {
                types::size length;

                while (i != end)
                {
                    fputc(*i++, fp_);
                    ++length;
                }

                total_ += length;
                return length;
            }

            void write(const char* data, types::size length)
            {
                std::fwrite(data, length, 1, fp_);
            }

            void write(types::size count, char c)
            {
                while (count--)
                {
                    std::putc(c, fp_);
                }
            }

        };
    }; // namespace detail

    BOOST_PP_REPEAT(BOOST_PP_ADD(FORMAT_MAX_ARGS, 1), FORMAT_STDIO_FUNC, 0)
}; // namespace format

#endif /* FORMAT_STDIO_HPP */
