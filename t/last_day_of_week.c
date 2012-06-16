#include "dt.h"
#include "tap.h"

const struct test {
    int  y;
    int  w;
    int  d;
    int  dow;
    int  ey;
    int  ew;
    int  ed;
} tests[] = {
    {2012, 10, 1, 1, 2012, 10, 7},
    {2012, 10, 1, 2, 2012, 10, 1},
    {2012, 10, 1, 3, 2012, 10, 2},
    {2012, 10, 1, 4, 2012, 10, 3},
    {2012, 10, 1, 5, 2012, 10, 4},
    {2012, 10, 1, 6, 2012, 10, 5},
    {2012, 10, 1, 7, 2012, 10, 6},
    {2012, 10, 1, 1, 2012, 10, 7},
    {2012, 10, 2, 2, 2012, 11, 1},
    {2012, 10, 3, 3, 2012, 11, 2},
    {2012, 10, 4, 4, 2012, 11, 3},
    {2012, 10, 5, 5, 2012, 11, 4},
    {2012, 10, 6, 6, 2012, 11, 5},
    {2012, 10, 7, 7, 2012, 11, 6},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ywd(t.y, t.w, t.d);
            dt_t got = dt_last_day_of_week(src, t.dow);
            dt_t exp = dt_from_ywd(t.ey, t.ew, t.ed);
            cmp_ok(got, "==", exp, "dt_last_day_of_week(%d, %d)", src, t.dow);
        }

        {
            dt_t src = dt_from_ywd(t.y, t.w, t.d);
            dt_t dt1 = dt_last_day_of_week(src, t.dow);
            dt_t dt2 = dt_first_day_of_week(src, t.dow) + 6;
            cmp_ok(dt1, "==", dt2, "dt_last_day_of_week(%d, %d) == dt_first_day_of_week(%d, %d) + 6", 
              src, t.dow, src, t.dow);
        }

    }
    done_testing();
}
