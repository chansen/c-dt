#include "dt.h"
#include "tap.h"
#include "first_day_of_quarter.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_yqd(t.y, t.q, t.d);
            dt_t got = dt_first_day_of_quarter(src, t.delta);
            dt_t exp = dt_from_yqd(t.ey, t.eq, t.ed);
            cmp_ok(got, "==", exp, "dt_first_day_of_quarter(%d, %d)", src, t.delta);
        }

        {
            dt_t src = dt_from_yqd(t.y, t.q, t.d);
            dt_t dt1 = dt_first_day_of_quarter(src, t.delta);
            dt_t dt2 = dt_last_day_of_quarter(src, t.delta - 1) + 1;
            cmp_ok(dt1, "==", dt2, "dt_first_day_of_quarter(%d, %d) == dt_last_day_of_quarter(%d, %d - 1) + 1",
              src, t.y, src, t.y);
        }

        {
            dt_t dt1 = dt_from_yqd(t.y, t.q, t.d);
            dt_t dt2 = dt_first_day_of_quarter(dt1, t.delta);
            int got = dt_delta_quarters(dt1, dt2, 0);
            cmp_ok(got, "==", t.delta, "dt_delta_quarters(%d, %d, false)", dt1, dt2);
        }
    }
    done_testing();
}

