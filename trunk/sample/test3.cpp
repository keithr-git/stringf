#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

int
main()
{
    char buf[1024];
    int length;

    length = format::outf(buf, sizeof(buf), "%.*f", 28,
            (double) 1 / (double) 3);
    printf("%d: %s\n", length, buf);
    length = format::outf(buf, sizeof(buf), "%.*f",
            __DBL_MAX_10_EXP__, __DBL_MIN__);
    printf("%d: %s\n", length, buf);
    return 0;
}
