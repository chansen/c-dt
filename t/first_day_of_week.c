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
    {2012, 10, 7, 1, 2012, 10, 1},
    {2012, 10, 7, 2, 2012, 10, 2},
    {2012, 10, 7, 3, 2012, 10, 3},
    {2012, 10, 7, 4, 2012, 10, 4},
    {2012, 10, 7, 5, 2012, 10, 5},
    {2012, 10, 7, 6, 2012, 10, 6},
    {2012, 10, 7, 7, 2012, 10, 7},
    {2012, 11, 1, 7, 2012, 10, 7},
    {2012, 10, 1, 1, 2012, 10, 1},
    {2012, 10, 2, 2, 2012, 10, 2},
    {2012, 10, 3, 3, 2012, 10, 3},
    {2012, 10, 4, 4, 2012, 10, 4},
    {2012, 10, 5, 5, 2012, 10, 5},
    {2012, 10, 6, 6, 2012, 10, 6},
    {2012, 10, 7, 7, 2012, 10, 7},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ywd(t.y, t.w, t.d);
            dt_t got = dt_first_day_of_week(src, t.dow);
            dt_t exp = dt_from_ywd(t.ey, t.ew, t.ed);
            cmp_ok(got, "==", exp, "dt_first_day_of_week(%d, %d)", src, t.dow);
        }

    }
    done_testing();
}
