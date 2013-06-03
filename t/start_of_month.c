#include "dt.h"
#include "tap.h"
#include "start_of_month.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_start_of_month(src, t.delta);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_start_of_month(%d (%.4d-%.2d-%.2d), %d)", 
              src, t.y, t.m, t.d, t.delta);
        }

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t dt1 = dt_start_of_month(src, t.delta);
            dt_t dt2 = dt_end_of_month(src, t.delta - 1) + 1;
            cmp_ok(dt1, "==", dt2, "dt_start_of_month(%d, %d) == dt_end_of_month(%d, %d - 1) + 1",
              src, t.y, src, t.y);
        }

        {
            dt_t dt1 = dt_from_ymd(t.y, t.m, t.d);
            dt_t dt2 = dt_start_of_month(dt1, t.delta);
            int got = dt_delta_months(dt1, dt2, 0);
            cmp_ok(got, "==", t.delta, "dt_delta_months(%d, %d, false)", dt1, dt2);
        }
    }
    done_testing();
}

