#include <stringf/stringf.hpp>

void mycopy(char* const __restrict__ dest, const char* const __restrict__ src)
{
    strcpy(dest, src);
}

void bar(char* const __restrict__ buf, size_t)
{
    mycopy(buf, "foobars");
}

void foo(char* __restrict__ buf, size_t bufsize)
{
    format::outf(buf, bufsize, "%s", "foobars");
}

int
main()
{
    return 0;
}
