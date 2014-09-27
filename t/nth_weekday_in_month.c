#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int nth;
    int ey;
    int em;
    int ed;
} tests[] = {
    {2010,  1,   1, 2010,  1,  1},
    {2011,  1,  -1, 2011,  1, 31},
    {2012,  1,   1, 2012,  1,  2},
    {2014, 12,   1, 2014, 12,  1},
    {2014, 12,   6, 2014, 12,  8},
    {2014, 12,  11, 2014, 12, 15},
    {2014, 12,  16, 2014, 12, 22},
    {2014, 12,  21, 2014, 12, 29},
    {2014, 12,  22, 2014, 12, 30},
    {2014, 12,  23, 2014, 12, 31},
    {2014, 12,  -1, 2014, 12, 31},
    {2014, 12,  -2, 2014, 12, 30},
    {2014, 12, -22, 2014, 12,  2},
    {2014, 12, -23, 2014, 12,  1},
    {2014,  3,  -1, 2014,  3, 31},
    {2014,  3,  -6, 2014,  3, 24},
    {2014,  3, -11, 2014,  3, 17},
    {2014,  3, -16, 2014,  3, 10},
    {2014,  3, -21, 2014,  3,  3},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_nth_weekday_in_month(t.y, t.m, t.nth);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_from_nth_weekday_in_month(%d, %d, %d)", t.y, t.m, t.nth);
        }

        {
            dt_t src = dt_from_ymd(t.y, t.m, 1);
            dt_t got = dt_nth_weekday_in_month(src, t.nth);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_nth_weekday_in_month(%d, %d)", src, t.nth);
        }

        {
            dt_t src = dt_from_nth_weekday_in_month(t.y, t.m, t.nth);
            int  got = dt_weekday_in_month(src, t.nth < 0);
            cmp_ok(got, "==", t.nth, "dt_weekday_in_month(%d, %s)", src, (t.nth < 0 ? "true" : "false"));
        }

    }
    done_testing();
}
