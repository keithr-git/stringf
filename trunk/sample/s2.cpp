#include <stringf/stringf.hpp>

void foo(char* __restrict__ buf, size_t bufsize)
{
    format::outf(buf, bufsize, "foobars");
}

int
main()
{
    return 0;
}
