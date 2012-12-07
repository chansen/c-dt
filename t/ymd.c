#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
    int dow;
    int rdn;
    int cjdn;
} tests[] = {
    /* Test cases extracted from <http://www.merlyn.demon.co.uk/ourdates.txt> */
    {1700,  1, 11, 1, 620558, 2341983},
    {1700,  2, 28, 7, 620606, 2342031},
    {1700,  3,  1, 1, 620607, 2342032},
    {1700,  3, 11, 4, 620617, 2342042},
    {1700,  3, 12, 5, 620618, 2342043},
    {1701,  1, 12, 3, 620924, 2342349},
    {1701,  3, 11, 5, 620982, 2342407},
    {1701,  3, 12, 6, 620983, 2342408},
    {1748,  1, 12, 5, 638090, 2359515},
    {1748,  3, 10, 7, 638148, 2359573},
    {1748,  3, 11, 1, 638149, 2359574},
    {1748,  3, 12, 2, 638150, 2359575},
    {1748,  4,  4, 4, 638173, 2359598},
    {1748,  4,  5, 5, 638174, 2359599},
    {1749,  1, 12, 7, 638456, 2359881},
    {1750,  1, 12, 1, 638821, 2360246},
    {1751,  1, 11, 1, 639185, 2360610},
    {1751,  1, 12, 2, 639186, 2360611},
    {1751,  4,  4, 7, 639268, 2360693},
    {1751,  4,  5, 1, 639269, 2360694},
    {1751,  4, 12, 1, 639276, 2360701},
    {1752,  1, 11, 2, 639550, 2360975},
    {1752,  1, 12, 3, 639551, 2360976},
    {1752,  2, 29, 2, 639599, 2361024},
    {1752,  3,  1, 3, 639600, 2361025},
    {1752,  3, 10, 5, 639609, 2361034},
    {1752,  3, 11, 6, 639610, 2361035},
    {1752,  3, 12, 7, 639611, 2361036},
    {1752,  9, 12, 2, 639795, 2361220},
    {1752,  9, 13, 3, 639796, 2361221},
    {1752,  9, 14, 4, 639797, 2361222},
    {1753,  1,  1, 1, 639906, 2361331},
    {1800,  1,  1, 3, 657072, 2378497},
    {1858, 11, 17, 3, 678576, 2400001},
    {1900,  1,  1, 1, 693596, 2415021},
    {1900,  2, 28, 3, 693654, 2415079},
    {1900,  3,  1, 4, 693655, 2415080},
    {1901,  1,  1, 2, 693961, 2415386},
    {1910,  1,  1, 6, 697248, 2418673},
    {1920,  1,  1, 4, 700900, 2422325},
    {1930,  1,  1, 3, 704553, 2425978},
    {1940,  1,  1, 1, 708205, 2429630},
    {1950,  1,  1, 7, 711858, 2433283},
    {1960,  1,  1, 5, 715510, 2436935},
    {1970,  1,  1, 4, 719163, 2440588},
    {1980,  1,  1, 2, 722815, 2444240},
    {1990,  1,  1, 1, 726468, 2447893},
    {1995, 10, 10, 2, 728576, 2450001},
    {2000,  1,  1, 6, 730120, 2451545},
    {2010,  1,  1, 5, 733773, 2455198},
    {2020,  1,  1, 3, 737425, 2458850},
    {2030,  1,  1, 2, 741078, 2462503},
    {2040,  1,  1, 7, 744730, 2466155},
    {2050,  1,  1, 6, 748383, 2469808},
    {2132,  8, 31, 7, 778575, 2500000},
    {2400, 12, 31, 7, 876582, 2598007},
    {2404, 12, 31, 5, 878043, 2599468},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int got = dt_rdn(dt_from_ymd(t.y, t.m, t.d));
            cmp_ok(got, "==", t.rdn, "dt_rdn(dt_from_ymd(%d, %d, %d))", t.y, t.m, t.d);
        }

        {
            int got = dt_rdn(dt_from_cjdn(t.cjdn));
            cmp_ok(got, "==", t.rdn, "dt_rdn(dt_from_cjdn(%d))", t.cjdn);
        }

        {
            int got = dt_cjdn(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.cjdn, "dt_cjdn(dt_from_rdn(%d))", t.rdn);
        }

        {
            int y, m, d;
            dt_to_ymd(dt_from_rdn(t.rdn), &y, &m, &d);
            if (!ok((y == t.y && m == t.m && d == t.d), "dt_to_ymd(dt_from_rdn(%d))", t.rdn)) {
                diag("      got: %.4d-%.2d-%.2d", y, m, d);
                diag("      exp: %.4d-%.2d-%.2d", t.y, t.m, t.d);
            }
        }

        {
            int got = dt_year(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.y, "dt_year(dt_from_rdn(%d))", t.rdn);
        }

        {
            int got = dt_month(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.m, "dt_month(dt_from_rdn(%d))", t.rdn);
        }

        {
            int got = dt_day(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.d, "dt_day(dt_from_rdn(%d))", t.rdn);
        }

        {
            int got = dt_day_of_week(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.dow, "dt_day_of_week(dt_from_rdn(%d))", t.rdn);
        }

        {
            ok(dt_valid_ymd(t.y, t.m, t.d), "dt_valid_ymd(%d, %d, %d)", t.y, t.m, t.d);
        }
    }
    done_testing();
}
