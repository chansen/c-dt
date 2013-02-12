#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int q;
    int d; 
    int delta;
    dt_adjust_t adjust;
    int ey;
    int eq;
    int ed;
} tests[] = {
    {2000, 1,  1,   1, DT_EXCESS, 2000, 2,  1},
    {2000, 1,  1,   2, DT_EXCESS, 2000, 3,  1},
    {2000, 1,  1,   3, DT_EXCESS, 2000, 4,  1},
    {2000, 1,  1,   4, DT_EXCESS, 2001, 1,  1},
    {2000, 1,  1,   4, DT_EXCESS, 2001, 1,  1},
    {2000, 1, 91,   1, DT_SNAP,   2000, 2, 91},
    {2000, 1, 91,   2, DT_SNAP,   2000, 3, 92},
    {2000, 1, 91,   3, DT_SNAP,   2000, 4, 92},
    {2001, 1, 90,   1, DT_SNAP,   2001, 2, 91},
    {2001, 1, 90,   2, DT_SNAP,   2001, 3, 92},
    {2001, 1, 90,   3, DT_SNAP,   2001, 4, 92},
    {2000, 4, 92,  -3, DT_LIMIT,  2000, 1, 91},
    {2001, 4, 92,  -3, DT_LIMIT,  2001, 1, 90},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_yqd(t.y, t.q, t.d);
            dt_t got = dt_add_quarters(src, t.delta, t.adjust);
            dt_t exp = dt_from_yqd(t.ey, t.eq, t.ed);
            cmp_ok(got, "==", exp, "dt_add_quarters(%d (%.4d-Q%d-%.2d), %d, %d)", 
              src, t.y, t.q, t.d, t.delta, t.adjust);
        }

        if (t.adjust != DT_EXCESS) {
            dt_t dt1 = dt_from_yqd(t.y, t.q, t.d);
            dt_t dt2 = dt_add_quarters(dt1, t.delta, t.adjust);
            int got = dt_delta_quarters(dt1, dt2);
            cmp_ok(got, "==", t.delta, "dt_delta_quarters(%d, %d)", dt1, dt2);
        }
    }
    done_testing();
}

