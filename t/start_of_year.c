#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
    int delta;
    int ey;
    int em;
    int ed;
} tests[] = {
    {2000,  2, 15, -19, 1981,  1,  1},
    {2001,  7, 27, -10, 1991,  1,  1},
    {2002,  6,  3,  14, 2016,  1,  1},
    {2003,  7, 12, -21, 1982,  1,  1},
    {2004,  8,  4,   9, 2013,  1,  1},
    {2005,  5, 15, -24, 1981,  1,  1},
    {2006,  4, 11,   3, 2009,  1,  1},
    {2007,  5,  5, -11, 1996,  1,  1},
    {2008, 11, 30,   3, 2011,  1,  1},
    {2009, 12, 16,   1, 2010,  1,  1},
    {2010, 10, 26, -20, 1990,  1,  1},
    {2011,  2, 28,  17, 2028,  1,  1},
    {2012, 11, 12,  -5, 2007,  1,  1},
    {2013, 11,  3, -20, 1993,  1,  1},
    {2014,  7, 29,  16, 2030,  1,  1},
    {2015,  6,  8,   2, 2017,  1,  1},
    {2016, 11,  9, -22, 1994,  1,  1},
    {2017,  6, 10,   2, 2019,  1,  1},
    {2018,  1, 20, -20, 1998,  1,  1},
    {2019,  3, 28,   0, 2019,  1,  1},
    {2020, 11, 15,  19, 2039,  1,  1},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_start_of_year(src, t.delta);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_start_of_year(%d, %d)", src, t.delta);
        }

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t dt1 = dt_start_of_year(src, t.delta);
            dt_t dt2 = dt_end_of_year(src, t.delta - 1) + 1;
            cmp_ok(dt1, "==", dt2, "dt_start_of_year(%d, %d) == dt_end_of_year(%d, %d - 1) + 1",
              src, t.y, src, t.y);
        }

        {
            dt_t dt1 = dt_from_ymd(t.y, t.m, t.d);
            dt_t dt2 = dt_start_of_year(dt1, t.delta);
            int got = dt_delta_years(dt1, dt2, 0);
            cmp_ok(got, "==", t.delta, "dt_delta_years(%d, %d, false)", dt1, dt2);
        }
    }
    done_testing();
}

