#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int q;
    int nth;
    int ey;
    int eq;
    int ed;
} tests[] = {
    {2010,  1,   1, 2010,  1,  1},
    {2010,  1,  -1, 2010,  1, 90},
    {2014,  1,   1, 2014,  1,  1},
    {2014,  1,   6, 2014,  1,  8},
    {2014,  1,  11, 2014,  1, 15},
    {2014,  1,  16, 2014,  1, 22},
    {2014,  1,  21, 2014,  1, 29},
    {2014,  1,  26, 2014,  1, 36},
    {2014,  1,  31, 2014,  1, 43},
    {2014,  1,  36, 2014,  1, 50},
    {2014,  1,  41, 2014,  1, 57},
    {2014,  1,  46, 2014,  1, 64},
    {2014,  1,  51, 2014,  1, 71},
    {2014,  1,  56, 2014,  1, 78},
    {2014,  1,  61, 2014,  1, 85},
    {2014,  1,  -1, 2014,  1, 90},
    {2014,  1,  -6, 2014,  1, 83},
    {2014,  1, -11, 2014,  1, 76},
    {2014,  1, -16, 2014,  1, 69},
    {2014,  1, -21, 2014,  1, 62},
    {2014,  1, -26, 2014,  1, 55},
    {2014,  1, -31, 2014,  1, 48},
    {2014,  1, -36, 2014,  1, 41},
    {2014,  1, -41, 2014,  1, 34},
    {2014,  1, -46, 2014,  1, 27},
    {2014,  1, -51, 2014,  1, 20},
    {2014,  1, -56, 2014,  1, 13},
    {2014,  1, -61, 2014,  1,  6},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_nth_weekday_in_quarter(t.y, t.q, t.nth);
            dt_t exp = dt_from_yqd(t.ey, t.eq, t.ed);
            cmp_ok(got, "==", exp, "dt_from_nth_weekday_in_quarter(%d, %d, %d)", t.y, t.q, t.nth);
        }

        {
            dt_t src = dt_from_yqd(t.y, t.q, 1);
            dt_t got = dt_nth_weekday_in_quarter(src, t.nth);
            dt_t exp = dt_from_yqd(t.ey, t.eq, t.ed);
            cmp_ok(got, "==", exp, "dt_nth_weekday_in_quarter(%d, %d)", src, t.nth);
        }

        {
            dt_t src = dt_from_nth_weekday_in_quarter(t.y, t.q, t.nth);
            int  got = dt_weekday_in_quarter(src, t.nth < 0);
            cmp_ok(got, "==", t.nth, "dt_weekday_in_quarter(%d, %s)", src, (t.nth < 0 ? "true" : "false"));
        }

    }
    done_testing();
}
