#include "dt.h"
#include "tap.h"
#include "add_months.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_add_months(src, t.delta, t.adjust);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_add_months(%d (%.4d-%.2d-%.2d), %d, %d)", 
              src, t.y, t.m, t.d, t.delta, t.adjust);
        }

        if (t.adjust != DT_EXCESS) {
            dt_t dt1 = dt_from_ymd(t.y, t.m, t.d);
            dt_t dt2 = dt_add_months(dt1, t.delta, t.adjust);
            int got = dt_delta_months(dt1, dt2);
            cmp_ok(got, "==", t.delta, "dt_delta_months(%d, %d)", dt1, dt2);
        }
    }
    done_testing();
}
