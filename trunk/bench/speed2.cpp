#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

#include <string>

#include <stringf/stringf.hpp>

#define SECONDS         3

volatile bool done = false;

void test_done(int)
{
    done = true;
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
    done = false;
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        snprintf(buf, sizeof(buf),
                "%s %s %s %s %s %s", "", "", "", "", "", "");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("snprintf", count, start, end);

    done = false;
    count = 0;
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        format::outf(buf, sizeof(buf),
                "%s %s %s %s %s %s", "", "", "", "", "", "");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("format(buf)", count, start, end);

    done = false;
    count = 0;
    s.reserve(512);
    alarm(SECONDS);
    getrusage(RUSAGE_SELF, &start);
    while (!done)
    {
        format::outf(s,
                "%s %s %s %s %s %s", "", "", "", "", "", "");
        ++count;
    }
    getrusage(RUSAGE_SELF, &end);
    print("format(string)", count, start, end);

    return 0;
}
