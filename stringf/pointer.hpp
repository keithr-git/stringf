#ifndef FORMAT_POINTER_HPP
#define FORMAT_POINTER_HPP

#include <boost/utility/enable_if.hpp>

namespace format
{
    namespace detail
    {
        struct pointer_type_tag
        { };

        template<typename T>
        struct type_tag<T*>
        {
            typedef pointer_type_tag    type;
        };

        template<typename Output, typename T>
        types::size format_pointer(Output& out, const format_spec& fspec,
                T* const& value)
        {
            switch (fspec.type)
            {
                case 'p':
                case 'P':
                    return format_value(out, fspec, (uintptr_t) value);
                    break;

                default:
                    return unknown_format(out, fspec, value, "pointer");
                    break;
            }
        }

        template<typename Output, typename T>
        typename boost::enable_if<boost::is_integral<T>, types::size>::type
        format_value(Output& out, const format_spec& fspec,
                T* const& value, pointer_type_tag)
        {
            if (fspec.type == 'n')
            {
                *value = out.total();
                return 0;
            }
            else
            {
                return format_pointer(out, fspec, value);
            }
        }

        template<typename Output, typename T>
        typename boost::disable_if<boost::is_integral<T>, types::size>::type
        format_value(Output& out, const format_spec& fspec,
                T* const& value, pointer_type_tag)
        {
            return format_pointer(out, fspec, value);
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_POINTER_HPP */
