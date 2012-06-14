#include "dt.h"
#include "tap.h"

const struct test {
    int  y;
    int  w;
    int  d;
    bool current;
    int  ey;
    int  ew;
    int  ed;
} tests[] = {
    {2012, 10, 1, 1, 2012, 10, 1},
    {2012, 10, 2, 1, 2012, 10, 2},
    {2012, 10, 3, 1, 2012, 10, 3},
    {2012, 10, 4, 1, 2012, 10, 4},
    {2012, 10, 5, 1, 2012, 10, 5},
    {2012, 10, 6, 1, 2012, 10, 5},
    {2012, 10, 7, 1, 2012, 10, 5},
    {2012, 10, 1, 0, 2012,  9, 5},
    {2012, 10, 2, 0, 2012, 10, 1},
    {2012, 10, 3, 0, 2012, 10, 2},
    {2012, 10, 4, 0, 2012, 10, 3},
    {2012, 10, 5, 0, 2012, 10, 4},
    {2012, 10, 6, 0, 2012, 10, 5},
    {2012, 10, 7, 0, 2012, 10, 5},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ywd(t.y, t.w, t.d);
            dt_t got = dt_prev_weekday(src, t.current);
            dt_t exp = dt_from_ywd(t.ey, t.ew, t.ed);
            cmp_ok(got, "==", exp, "dt_prev_weekday(%d, %d)", src, t.current);
        }

    }
    done_testing();
}
