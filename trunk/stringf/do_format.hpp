#ifndef FORMAT_DO_FORMAT_HPP
#define FORMAT_DO_FORMAT_HPP

#include <boost/type_traits.hpp>
#include <boost/variant.hpp>

namespace format
{
    namespace detail
    {
        template<typename Output>
        class formatter : public boost::static_visitor<types::size>
        {
            Output&                 output_;
            const format_spec&      fspec_;

        public:
            formatter(Output& output, const format_spec& fspec)
                : output_(output), fspec_(fspec)
            { }

            template<typename T>
            types::size operator()(const T& value) const
            {
                return format_value(output_, fspec_, value);
            }
        };

        class get_width : public boost::static_visitor<types::size>
        {
        public:
            template<typename T>
            typename boost::enable_if<boost::is_arithmetic<T>,
                    types::size>::type
            operator()(const T& value) const
            {
                return static_cast<types::size>(value);
            }

            template<typename T>
            typename boost::disable_if<boost::is_arithmetic<T>,
                    types::size>::type
            operator()(const T&) const
            {
                throw index_error("Non-arithemetic type used for index");
                return 0;
            }
        };

        template<typename Output, typename Char, typename Variant>
        types::size do_format(Output& out, const Char* __restrict__ format,
            Variant* args, types::size num_args)
        {
            format_spec fspec;
            const Char* prefix;
            types::size prefix_length;
            types::size next_arg = 0;

            while (format)
            {
                types::size arg_index = next_arg;
                types::size length;

                parse(format, fspec, arg_index, prefix, prefix_length);

                if (fspec.type != 0 && arg_index >= num_args)
                {
                    throw argument_error("Too few arguments for format");
                }

                if (prefix_length)
                {
                    out.write(prefix, prefix_length);
                }

                if (fspec.type == 0)
                {
                    break;
                }

                if (fspec.width_index)
                {
                    fspec.width = boost::apply_visitor(get_width(),
                            args[fspec.width]);
                }

                if (fspec.precision_index)
                {
                    fspec.precision = boost::apply_visitor(get_width(),
                            args[fspec.precision]);
                }

                if (fspec.type != '%')
                {
                    length = boost::apply_visitor(formatter<Output>(out, fspec),
                            args[arg_index]);
                    if (length < 0)
                    {
                        return length;
                    }
                    next_arg = arg_index + 1;
                }
            }

            if (next_arg != num_args)
            {
                throw argument_error("Too many arguments for format");
            }

            return out.total();
        }

        struct unknown_type_tag
        { };

        template<typename T, typename Enabled = void>
        struct type_tag
        {
            typedef unknown_type_tag    type;
        };

        //
        // Remove const and volatile qualifiers from the type, to
        // minimize the number of specializations of type_tag
        // required (e.g. char*, const char*, volatilie char*, etc).
        // We can't just use boost::remove_cv<> here, because that
        // doesn't do what we want for pointers.  It removes the
        // const and volatile qualifiers from the pointer, but not
        // from the pointed-to type.
        // 
        template<typename T>
        struct basic_type
        {
        private:
            typedef BOOST_DEDUCED_TYPENAME boost::remove_reference<T>::type Ty;

        public:
            typedef BOOST_DEDUCED_TYPENAME boost::mpl::eval_if<
                boost::is_pointer<Ty>,
                boost::add_pointer<
                    BOOST_DEDUCED_TYPENAME boost::remove_cv<
                        BOOST_DEDUCED_TYPENAME boost::remove_pointer<Ty>::type
                    >::type
                >,
                boost::mpl::identity<Ty>
            >::type type;
        };

        //
        // To provide a format_value overload for multiple types
        // using a template, we use tag-based dispatching.  The
        // type_tag struct provides the tag, and the format_value
        // template function takes the tag as an extra argument
        // so the compiler can find it.
        //
        // To provide a format_value() overload for a single type,
        // we just use a non-template function (or, rather, a
        // template for the output type, but not for the value
        // type).
        //
        template<typename Output, typename T, typename Tag>
        types::size format_value(Output& out, const format_spec& fspec,
                const T& value, Tag);

        template<typename Output, typename T>
        types::size format_value(Output& out, const format_spec& fspec,
                const T& value)
        {
            typename type_tag< typename basic_type<T>::type >::type tag;

            return format_value(out, fspec, value, tag);
        }
    }; // namespace detail
}; // namespace format

#endif /* FORMAT_DO_FORMAT_HPP */
