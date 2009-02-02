#include <stringf/stringf.hpp>
#include <stringf/stdio.hpp>

#include <stdio.h>

int
main()
{
    format::outf(stdout, "%s\n", "foo");
}
