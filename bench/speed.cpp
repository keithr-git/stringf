//
//    Copyright 2008, 2009 Keith Reynolds.
//
//    This file is part of Stringf.
//
//    Stringf is free software: you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation,
//    either version 2.1 of the License, or (at your option) any
//    later version.
//
//    Stringf is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty
//    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//    See the GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General
//    Public License along with Stringf.  If not, see
//    <http://www.gnu.org/licenses/>.
//
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

#include <string>

#include <stringf/stringf.hpp>

#define SECONDS         3

volatile sig_atomic_t done = 0;

void test_done(int)
{
    done = 1;
}

void print(const char* const label, unsigned long long count,
        const struct rusage& start, const struct rusage& end)
{
    unsigned long long elapsed;

    elapsed = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * 1000000000ULL;
    elapsed += (end.ru_utime.tv_usec - start.ru_utime.tv_usec) * 1000ULL;
    elapsed += (end.ru_stime.tv_sec - start.ru_stime.tv_sec) * 1000000000ULL;
    elapsed += (end.ru_stime.tv_usec - start.ru_stime.tv_usec) * 1000ULL;
    printf("%s: %llu iterations in %llu ns, %llu ns/iteration\n",
            label, count, elapsed, elapsed / count);
}

int
main()
{
    char buf[1024];
    struct sigaction alarm_action;
    struct rusage start;
    struct rusage end;
    unsigned long long count;
    std::string s;

    memset(&alarm_action, 0, sizeof(alarm_action));
    alarm_action.sa_handler = test_done;
    alarm_action.sa_flags = 0;
    sigaction(SIGALRM, &alarm_action, 0);

    alarm(1);
    count = 0;
    while (!done)
    {
        ++count;
    }

    count = 0;
    done = 0;
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        snprintf(buf, sizeof(buf), "value: %s", "foo");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("snprintf", count, start, end);

    done = 0;
    count = 0;
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        format::outf(buf, sizeof(buf), "value: %s", "foo");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("format(buf)", count, start, end);

    done = 0;
    count = 0;
    s.reserve(512);
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        format::outf(s, "value: %s", "foo");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("format(string)", count, start, end);

    return 0;
}
