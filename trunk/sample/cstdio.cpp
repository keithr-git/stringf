#include <stringf/stringf.hpp>
#include <stringf/stdio.hpp>

#include <cstdio>

int
main()
{
    format::outf(stdout, "%s\n", "foo");
}
