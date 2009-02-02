#include <string>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using format::stringf;
using format::outf;

int
main()
{
    std::string s;
    // short i = 1;
    // int j = 2;
    // long k = 3;
    unsigned int l = 4;
    const unsigned int L = 42;
    const char* foo = "foo";
    const char* const baz = "baz";

    // s = stringf("%d %d %d %d", i, j, k, l);
    // outf("%d: %s\n", s.size(), s.c_str());
    s = stringf("%s %d", foo, l);
    outf("%d: %s\n", s.size(), s.c_str());
    outf(L"%d: %s\n", s.size(), s.c_str());
    s = stringf("%d %s", l, "bar");
    outf("%d: %s\n", s.size(), s.c_str());
    s = stringf("%d %s %d %d %s %s", l, "bar", l, L, foo, baz);
    outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf(buf, "%d", l);
    // outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf("%s %s", "foo", "bar");
    // outf("%d: %s\n", s.size(), s.c_str());
    // s = stringf("%s", foo);
    return 0;
}
