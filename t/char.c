#include <string.h>
#include "dt.h"
#include "tap.h"

int 
main() {
    
    #define DT_CHAR(F) ("DT_CHAR_"#F), (DT_CHAR_##F)
    {
        const struct test {
            const char *name;
            unsigned char flag;
            size_t exp;
            const char *str;
        } tests[] = {
            { DT_CHAR(HSPACE),  2, " \t"                                  }, 
            { DT_CHAR(VSPACE),  2, "\r\n"                                 },
            { DT_CHAR(SPACE),   4, " \t\r\n"                              },
            { DT_CHAR(PUNCT),  32, "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"   },
            { DT_CHAR(DIGIT),  10, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
            { DT_CHAR(ALNUM),  36, "0123456789ABCDEFGHIJKLMnopqrstuvwxyz" },
            { DT_CHAR(ALPHA),  26, "ABCDEFGHIJKLMnopqrstuvwxyz0123456789" },
            { DT_CHAR(UPPER),  26, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghij" },
            { DT_CHAR(LOWER),  26, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJ" },
        };
        size_t i, ntests, got;

        ntests = sizeof(tests) / sizeof(*tests);
        for (i = 0; i < ntests; i++) {
            const struct test t = tests[i];

            got = dt_char_span((const unsigned char *)t.str, strlen(t.str), t.flag);
            cmp_ok(got, "==", t.exp, "dt_char_span(\"%s\", %s)", t.str, t.name);
        }
    }

    {
        const struct test {
            const char *name;
            unsigned char flag;
            size_t exp;
            const char *str;
        } tests[] = {
            { DT_CHAR(ALPHA),  10, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
            { DT_CHAR(LOWER),  23, "0123456789ABCDEFGHIJKLMnopqrstuvwxyz" },
            { DT_CHAR(UPPER),  26, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJ" },
            { DT_CHAR(DIGIT),  26, "ABCDEFGHIJKLMnopqrstuvwxyz0123456789" },
            { DT_CHAR(ALPHA),   0, "ABCDEFGHIJKLMnopqrstuvwxyz0123456789" },
        };
        size_t i, ntests, got;

        ntests = sizeof(tests) / sizeof(*tests);
        for (i = 0; i < ntests; i++) {
            const struct test t = tests[i];

            got = dt_char_span_until((const unsigned char *)t.str, strlen(t.str), t.flag);
            cmp_ok(got, "==", t.exp, "dt_char_span_until(\"%s\", %s)", t.str, t.name);
        }
    }

    done_testing();
}
