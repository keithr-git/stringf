#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

int
main()
{
    char buf[1024];
    double d = 1042.0371;
    int length;
    short s = -1;
    unsigned short us = 1;
    int i = -2;
    int ui = 2;
    long l = -3;
    unsigned long ul = 3;

    length = format::outf(buf, sizeof(buf), "%d %f", i, d);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%+f %d", d, i);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %u %d %u %d %u %e", s, us, i, ui, l, ul, d);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%d %u %d %u %d %u %'f", l, ul, i, ui, s, us, d);
    printf("%d: %s\n", length, buf);
    return 0;
}
