#include <string>
#include <iostream>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using std::string;
using namespace format;

int
main(int, char * const *argv)
{
    int len(0);

    format::outf(std::cout, "%p %s\n", argv[0], argv[0]);
    format::outf(std::cout, "%p\n", (void*) argv);
    format::outf("%p%n\n", argv[0], &len);
    format::outf("%d\n", len);
}
