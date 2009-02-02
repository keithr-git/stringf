#include <iostream>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

int
main()
{
    char buf[4096];

    try
    {
        format::outf(buf, sizeof(buf), "%z", 5);
    }
    catch (format::parse_error& e)
    {
        format::outf(std::cerr, "parse error: %s\n", e.what());
    }
    catch (format::exception::base& e)
    {
        if (e.is<format::argument_error>())
        {
            format::outf(std::cerr, "argument error: %s\n", e.what());
        }
        else
        {
            format::outf(std::cerr, "format error: %s\n", e.what());
        }
    }
}
