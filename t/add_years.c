#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int d;
    int delta;
    dt_adjust_t adjust;
    int ey;
    int ed;
} tests[] = {
    {2000,   1,   1, DT_EXCESS, 2001,   1},
    {2000, 365,   1, DT_EXCESS, 2001, 365},
    {2000, 366,   1, DT_EXCESS, 2002,   1},
    {2000, 366,   1, DT_LIMIT,  2001, 365},
    {2001, 365,   3, DT_LIMIT,  2004, 365},
    {2001, 365,   3, DT_EXCESS, 2004, 365},
    {2001, 365,   3, DT_SNAP,   2004, 366},
    {2000, 366,   1, DT_SNAP,   2001, 365},
};

int
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_yd(t.y, t.d);
            dt_t got = dt_add_years(src, t.delta, t.adjust);
            dt_t exp = dt_from_yd(t.ey, t.ed);
            cmp_ok(got, "==", exp, "dt_add_years(%d (%.4d-%.3d), %d, %d)",
              src, t.y, t.d, t.delta, t.adjust);
        }

        if (t.adjust != DT_EXCESS) {
            dt_t dt1 = dt_from_yd(t.y, t.d);
            dt_t dt2 = dt_add_years(dt1, t.delta, t.adjust);
            int got = dt_delta_years(dt1, dt2);
            cmp_ok(got, "==", t.delta, "dt_delta_years(%d, %d)", dt1, dt2);
        }
    }
    done_testing();
}

