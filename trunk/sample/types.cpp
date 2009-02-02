#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

typedef unsigned int    i1;
typedef int    i2;
typedef unsigned int    i3;
typedef i2              i4;

int
main()
{
    // unsigned int i(0);
    i1 i1(1);
    i2 i2(2);
    // i3 i3(3);
    // i4 i4(4);
    // size_t size(5);

    format::outf("%d %d\n", i1, i2);
    format::outf("%d %d\n", i2, i1);
    // format::outf("%d\n", i);
    // format::outf("%d %d\n", i, i1);
    // format::outf("%d %d %d\n", i, i1, i2);
    // format::outf("%d %d %d %d\n", i, i1, i2, i3);
    // format::outf("%d %d %d %d %d\n", i, i1, i2, i3, i4);
    // format::outf("%d %d %d %d %d %d\n", i, i1, i2, i3, i4, size);
}
