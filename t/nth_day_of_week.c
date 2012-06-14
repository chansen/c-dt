#include "dt.h"
#include "tap.h"
#include "nth_day_of_week.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_nth_day_of_week(src, t.nth, t.dow);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_nth_day_of_week(%d (%.4d-%.2d-%.2d), %d, %d)", 
              src, t.y, t.m, t.d, t.nth, t.dow);
        }

    }
    done_testing();
}
