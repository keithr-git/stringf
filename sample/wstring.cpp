#include <string>
#include <iostream>

#include <stringf/stringf.hpp>
#include <stringf/ostream.hpp>

using std::wstring;
using namespace format;

int
main(int, char * const *)
{
    wstring s;
    int length;
    // short i = 1;
    // int j = 2;
    // long k = 3;
    unsigned int l = 4;
    const char* foo = "foo";
    wstring baz(L"baz");

    // length = format::outf(s, "%d %d %d %d", i, j, k, l);
    // format::outf(std::cout, "%d: %s\n", length, buf);
    length = format::outf(s, L"%s %d", foo, l);
    format::outf(std::cout, "%d: %s\n", length, s.c_str());
    length = format::outf(s, L"%d %s", l, "bar");
    format::outf(std::cout, "%d: %s\n", length, s.c_str());
    length = format::outf(s, L"%d %s", l, baz);
    format::outf(std::cout, "%d: %s\n", length, s.c_str());
    // length = format::outf(s, "%s %s", "foo", "bar");
    // format::outf(std::cout, "%d: %s\n", length, buf);
    // length = format::outf(s, "%s", foo);
    return 0;
}
