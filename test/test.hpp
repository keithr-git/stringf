#ifndef TEST_HPP
#define TEST_HPP

#define TRY_LIMITED(limit, fmt, ...) \
    { \
        char buf1[4096], buf2[4096]; \
        int len1, len2; \
        bool match; \
        len1 = format::outf(buf1, sizeof(buf1), fmt, ## __VA_ARGS__); \
        len2 = snprintf(buf2, sizeof(buf2), fmt, ## __VA_ARGS__); \
        if (len1 != len2) { \
            char errbuf[512]; \
            snprintf(errbuf, sizeof(errbuf), \
                    "format(%s): length is %d, should be %d", \
                    fmt, len1, len2); \
            BOOST_ERROR(errbuf); \
        } \
        if (limit == -1) { \
            match = strcmp(buf1, buf2) == 0; \
        } else { \
            match = strncmp(buf1, buf2, limit) == 0; \
        } \
        if (!match) { \
            char errbuf[9216]; \
            snprintf(errbuf, sizeof(errbuf), \
                    "format(%s): '%s' should be '%s'", \
                    fmt, buf1, buf2); \
            BOOST_ERROR(errbuf); \
        } \
    }

#define TRY(fmt, ...)   TRY_LIMITED(-1, fmt, ## __VA_ARGS__)

#endif /* TEST_HPP */
