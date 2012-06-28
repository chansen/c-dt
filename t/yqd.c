#define DT_INTERNAL
#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int q;
    int d;
    dt_t dt;
} tests[] = {
    {2000, 1, 38, 730157 - EPOCH_OFFSET},
    {2000, 2, 21, 730231 - EPOCH_OFFSET},
    {2000, 3, 82, 730383 - EPOCH_OFFSET},
    {2000, 4, 11, 730404 - EPOCH_OFFSET},
    {2001, 1, 60, 730545 - EPOCH_OFFSET},
    {2001, 2, 67, 730642 - EPOCH_OFFSET},
    {2001, 3, 35, 730701 - EPOCH_OFFSET},
    {2001, 4, 52, 730810 - EPOCH_OFFSET},
    {2002, 1, 14, 730864 - EPOCH_OFFSET},
    {2002, 2, 55, 730995 - EPOCH_OFFSET},
    {2002, 3, 50, 731081 - EPOCH_OFFSET},
    {2002, 4, 47, 731170 - EPOCH_OFFSET},
    {2003, 1, 38, 731253 - EPOCH_OFFSET},
    {2003, 2, 25, 731330 - EPOCH_OFFSET},
    {2003, 3, 28, 731424 - EPOCH_OFFSET},
    {2003, 4,  2, 731490 - EPOCH_OFFSET},
    {2004, 1, 69, 731649 - EPOCH_OFFSET},
    {2004, 2, 13, 731684 - EPOCH_OFFSET},
    {2004, 3, 91, 731853 - EPOCH_OFFSET},
    {2004, 4, 79, 731933 - EPOCH_OFFSET},
    {2005, 1, 41, 731987 - EPOCH_OFFSET},
    {2005, 2, 16, 732052 - EPOCH_OFFSET},
    {2005, 3, 20, 732147 - EPOCH_OFFSET},
    {2005, 4, 81, 732300 - EPOCH_OFFSET},
    {2006, 1, 20, 732331 - EPOCH_OFFSET},
    {2006, 2, 11, 732412 - EPOCH_OFFSET},
    {2006, 3, 12, 732504 - EPOCH_OFFSET},
    {2006, 4, 55, 732639 - EPOCH_OFFSET},
    {2007, 1, 68, 732744 - EPOCH_OFFSET},
    {2007, 2, 27, 732793 - EPOCH_OFFSET},
    {2007, 3, 81, 732938 - EPOCH_OFFSET},
    {2007, 4, 21, 732970 - EPOCH_OFFSET},
    {2008, 1, 54, 733095 - EPOCH_OFFSET},
    {2008, 2, 27, 733159 - EPOCH_OFFSET},
    {2008, 3, 81, 733304 - EPOCH_OFFSET},
    {2008, 4, 66, 733381 - EPOCH_OFFSET},
    {2009, 1, 74, 733481 - EPOCH_OFFSET},
    {2009, 2, 30, 733527 - EPOCH_OFFSET},
    {2009, 3, 17, 733605 - EPOCH_OFFSET},
    {2009, 4, 85, 733765 - EPOCH_OFFSET},
    {2010, 1, 84, 733856 - EPOCH_OFFSET},
    {2010, 2, 85, 733947 - EPOCH_OFFSET},
    {2010, 3,  6, 733959 - EPOCH_OFFSET},
    {2010, 4, 51, 734096 - EPOCH_OFFSET},
    {2011, 1, 51, 734188 - EPOCH_OFFSET},
    {2011, 2, 39, 734266 - EPOCH_OFFSET},
    {2011, 3,  2, 734320 - EPOCH_OFFSET},
    {2011, 4, 62, 734472 - EPOCH_OFFSET},
    {2012, 1, 17, 734519 - EPOCH_OFFSET},
    {2012, 2, 56, 734649 - EPOCH_OFFSET},
    {2012, 3, 89, 734773 - EPOCH_OFFSET},
    {2012, 4,  2, 734778 - EPOCH_OFFSET},
    {2013, 1, 21, 734889 - EPOCH_OFFSET},
    {2013, 2, 38, 734996 - EPOCH_OFFSET},
    {2013, 3, 90, 735139 - EPOCH_OFFSET},
    {2013, 4, 14, 735155 - EPOCH_OFFSET},
    {2014, 1, 24, 735257 - EPOCH_OFFSET},
    {2014, 2, 39, 735362 - EPOCH_OFFSET},
    {2014, 3, 49, 735463 - EPOCH_OFFSET},
    {2014, 4, 11, 735517 - EPOCH_OFFSET},
    {2015, 1, 87, 735685 - EPOCH_OFFSET},
    {2015, 2, 80, 735768 - EPOCH_OFFSET},
    {2015, 3, 72, 735851 - EPOCH_OFFSET},
    {2015, 4, 34, 735905 - EPOCH_OFFSET},
    {2016, 1, 59, 736022 - EPOCH_OFFSET},
    {2016, 2, 23, 736077 - EPOCH_OFFSET},
    {2016, 3, 35, 736180 - EPOCH_OFFSET},
    {2016, 4, 60, 736297 - EPOCH_OFFSET},
    {2017, 1,  7, 736336 - EPOCH_OFFSET},
    {2017, 2, 32, 736451 - EPOCH_OFFSET},
    {2017, 3,  8, 736518 - EPOCH_OFFSET},
    {2017, 4,  4, 736606 - EPOCH_OFFSET},
    {2018, 1, 12, 736706 - EPOCH_OFFSET},
    {2018, 2, 91, 736875 - EPOCH_OFFSET},
    {2018, 3, 17, 736892 - EPOCH_OFFSET},
    {2018, 4, 42, 737009 - EPOCH_OFFSET},
    {2019, 1, 35, 737094 - EPOCH_OFFSET},
    {2019, 2, 16, 737165 - EPOCH_OFFSET},
    {2019, 3, 81, 737321 - EPOCH_OFFSET},
    {2019, 4, 77, 737409 - EPOCH_OFFSET},
    {2020, 1, 82, 737506 - EPOCH_OFFSET},
    {2020, 2, 12, 737527 - EPOCH_OFFSET},
    {2020, 3, 12, 737618 - EPOCH_OFFSET},
    {2020, 4, 60, 737758 - EPOCH_OFFSET},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_yqd(t.y, t.q, t.d);
            cmp_ok(got, "==", t.dt, "dt_from_yqd(%d, %d, %d)", t.y, t.q, t.d);
        }

        {
            int y, q, d;
            dt_to_yqd(t.dt, &y, &q, &d);
            if (!ok((y == t.y && q == t.q && d == t.d), "dt_to_yqd(%d)", t.dt)) {
                diag("     got: %.4d-Q%d-%.2d", y, q, d);
                diag("     exp: %.4d-Q%d-%.2d", t.y, t.q, t.d);
            }
        }

        {
            int got = dt_year(t.dt);
            cmp_ok(got, "==", t.y, "dt_year(%d)", t.dt);
        }

        {
            int got = dt_quarter(t.dt);
            cmp_ok(got, "==", t.q, "dt_quarter(%d)", t.dt);
        }

        {
            int got = dt_day_of_quarter(t.dt);
            cmp_ok(got, "==", t.d, "dt_day_of_quarter(%d)", t.dt);
        }

        {
            ok(dt_valid_yqd(t.y, t.q, t.d), "dt_valid_yqd(%d, %d, %d)", t.y, t.q, t.d);
        }

    }
    done_testing();
}
