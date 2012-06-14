#include "dt.h"
#include "tap.h"
#include "easter_orthodox.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t exp = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_from_easter(t.y, DT_ORTHODOX);
            cmp_ok(got, "==", exp, "dt_from_easter(%d, DT_ORTHODOX)", t.y);
        }
    }

    {
        dt_t got = dt_from_easter(-1, DT_ORTHODOX);
        cmp_ok(got, "==", 0, "dt_from_easter(-1, DT_ORTHODOX)");
    }

    {
        dt_t got = dt_from_easter(0, DT_ORTHODOX);
        cmp_ok(got, "==", 0, "dt_from_easter(0, DT_ORTHODOX)");
    }

    done_testing();
}
