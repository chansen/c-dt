#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int nth;
    int ey;
    int ed;
} tests[] = {
    {2014,    1, 2014,   1},
    {2014,   16, 2014,  22},
    {2014,   31, 2014,  43},
    {2014,   46, 2014,  64},
    {2014,   61, 2014,  85},
    {2014,   76, 2014, 106},
    {2014,   91, 2014, 127},
    {2014,  106, 2014, 148},
    {2014,  121, 2014, 169},
    {2014,  136, 2014, 190},
    {2014,  151, 2014, 211},
    {2014,  166, 2014, 232},
    {2014,  181, 2014, 253},
    {2014,  196, 2014, 274},
    {2014,  211, 2014, 295},
    {2014,  226, 2014, 316},
    {2014,  241, 2014, 337},
    {2014,  256, 2014, 358},
    {2014,   -1, 2014, 365},
    {2014,  -16, 2014, 344},
    {2014,  -31, 2014, 323},
    {2014,  -46, 2014, 302},
    {2014,  -61, 2014, 281},
    {2014,  -76, 2014, 260},
    {2014,  -91, 2014, 239},
    {2014, -106, 2014, 218},
    {2014, -121, 2014, 197},
    {2014, -136, 2014, 176},
    {2014, -151, 2014, 155},
    {2014, -166, 2014, 134},
    {2014, -181, 2014, 113},
    {2014, -196, 2014,  92},
    {2014, -211, 2014,  71},
    {2014, -226, 2014,  50},
    {2014, -241, 2014,  29},
    {2014, -256, 2014,   8},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_nth_weekday_in_year(t.y, t.nth);
            dt_t exp = dt_from_yd(t.ey, t.ed);
            cmp_ok(got, "==", exp, "dt_from_nth_weekday_in_year(%d, %d)", t.y, t.nth);
        }

        {
            dt_t src = dt_from_yd(t.y, 1);
            dt_t got = dt_nth_weekday_in_year(src, t.nth);
            dt_t exp = dt_from_yd(t.ey, t.ed);
            cmp_ok(got, "==", exp, "dt_nth_weekday_in_year(%d, %d)", src, t.nth);
        }

        {
            dt_t src = dt_from_nth_weekday_in_year(t.y, t.nth);
            int  got = dt_weekday_in_year(src, t.nth < 0);
            cmp_ok(got, "==", t.nth, "dt_weekday_in_year(%d, %s)", src, (t.nth < 0 ? "true" : "false"));
        }

    }
    done_testing();
}
