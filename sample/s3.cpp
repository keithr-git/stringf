#include <string>
#include <stringf/stringf.hpp>

void foo(std::string& buf)
{
    format::outf(buf, "foobars");
}

int
main()
{
    std::string s;

    foo(s);
    return 0;
}
