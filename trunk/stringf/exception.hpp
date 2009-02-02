#ifndef FORMAT_EXCEPTION_HPP
#define FORMAT_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace format
{
    namespace exception
    {
        struct PARSE_ERROR      { enum { code = 1 }; };
        struct ARGUMENT_ERROR   { enum { code = 2 }; };
        struct INDEX_ERROR      { enum { code = 3 }; };
        struct FORMAT_ERROR     { enum { code = 4 }; };

        class base : public std::runtime_error
        {
            int             code_;

        public:
            base(int code, const std::string& message)
                : std::runtime_error(message), code_(code)
            { }

            template <typename EXCEPTION>
            inline bool is() const
            {
                return code_ == EXCEPTION::code();
            }
        };

        template <typename EXCEPTION>
        class exception : public base
        {
        public:
            exception(const std::string& message)
                : base(EXCEPTION::code, message)
            { }

            static int code()
            {
                return EXCEPTION::code;
            }
        };
    };

    typedef exception::exception<exception::PARSE_ERROR>        parse_error;
    typedef exception::exception<exception::ARGUMENT_ERROR>     argument_error;
    typedef exception::exception<exception::INDEX_ERROR>        index_error;
    typedef exception::exception<exception::FORMAT_ERROR>       format_error;
};

#endif /* FORMAT_EXCEPTION_HPP */
