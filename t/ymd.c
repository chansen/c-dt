#define DT_INTERNAL
#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
    int dow;
    dt_t dt;
    int cjdn;
} tests[] = {
    /* Test cases extracted from <http://www.merlyn.demon.co.uk/ourdates.txt> */
    {1700,  1, 11, 1, 620558 - EPOCH_OFFSET, 2341983},
    {1700,  2, 28, 7, 620606 - EPOCH_OFFSET, 2342031},
    {1700,  3,  1, 1, 620607 - EPOCH_OFFSET, 2342032},
    {1700,  3, 11, 4, 620617 - EPOCH_OFFSET, 2342042},
    {1700,  3, 12, 5, 620618 - EPOCH_OFFSET, 2342043},
    {1701,  1, 12, 3, 620924 - EPOCH_OFFSET, 2342349},
    {1701,  3, 11, 5, 620982 - EPOCH_OFFSET, 2342407},
    {1701,  3, 12, 6, 620983 - EPOCH_OFFSET, 2342408},
    {1748,  1, 12, 5, 638090 - EPOCH_OFFSET, 2359515},
    {1748,  3, 10, 7, 638148 - EPOCH_OFFSET, 2359573},
    {1748,  3, 11, 1, 638149 - EPOCH_OFFSET, 2359574},
    {1748,  3, 12, 2, 638150 - EPOCH_OFFSET, 2359575},
    {1748,  4,  4, 4, 638173 - EPOCH_OFFSET, 2359598},
    {1748,  4,  5, 5, 638174 - EPOCH_OFFSET, 2359599},
    {1749,  1, 12, 7, 638456 - EPOCH_OFFSET, 2359881},
    {1750,  1, 12, 1, 638821 - EPOCH_OFFSET, 2360246},
    {1751,  1, 11, 1, 639185 - EPOCH_OFFSET, 2360610},
    {1751,  1, 12, 2, 639186 - EPOCH_OFFSET, 2360611},
    {1751,  4,  4, 7, 639268 - EPOCH_OFFSET, 2360693},
    {1751,  4,  5, 1, 639269 - EPOCH_OFFSET, 2360694},
    {1751,  4, 12, 1, 639276 - EPOCH_OFFSET, 2360701},
    {1752,  1, 11, 2, 639550 - EPOCH_OFFSET, 2360975},
    {1752,  1, 12, 3, 639551 - EPOCH_OFFSET, 2360976},
    {1752,  2, 29, 2, 639599 - EPOCH_OFFSET, 2361024},
    {1752,  3,  1, 3, 639600 - EPOCH_OFFSET, 2361025},
    {1752,  3, 10, 5, 639609 - EPOCH_OFFSET, 2361034},
    {1752,  3, 11, 6, 639610 - EPOCH_OFFSET, 2361035},
    {1752,  3, 12, 7, 639611 - EPOCH_OFFSET, 2361036},
    {1752,  9, 12, 2, 639795 - EPOCH_OFFSET, 2361220},
    {1752,  9, 13, 3, 639796 - EPOCH_OFFSET, 2361221},
    {1752,  9, 14, 4, 639797 - EPOCH_OFFSET, 2361222},
    {1753,  1,  1, 1, 639906 - EPOCH_OFFSET, 2361331},
    {1800,  1,  1, 3, 657072 - EPOCH_OFFSET, 2378497},
    {1858, 11, 17, 3, 678576 - EPOCH_OFFSET, 2400001},
    {1900,  1,  1, 1, 693596 - EPOCH_OFFSET, 2415021},
    {1900,  2, 28, 3, 693654 - EPOCH_OFFSET, 2415079},
    {1900,  3,  1, 4, 693655 - EPOCH_OFFSET, 2415080},
    {1901,  1,  1, 2, 693961 - EPOCH_OFFSET, 2415386},
    {1910,  1,  1, 6, 697248 - EPOCH_OFFSET, 2418673},
    {1920,  1,  1, 4, 700900 - EPOCH_OFFSET, 2422325},
    {1930,  1,  1, 3, 704553 - EPOCH_OFFSET, 2425978},
    {1940,  1,  1, 1, 708205 - EPOCH_OFFSET, 2429630},
    {1950,  1,  1, 7, 711858 - EPOCH_OFFSET, 2433283},
    {1960,  1,  1, 5, 715510 - EPOCH_OFFSET, 2436935},
    {1970,  1,  1, 4, 719163 - EPOCH_OFFSET, 2440588},
    {1980,  1,  1, 2, 722815 - EPOCH_OFFSET, 2444240},
    {1990,  1,  1, 1, 726468 - EPOCH_OFFSET, 2447893},
    {1995, 10, 10, 2, 728576 - EPOCH_OFFSET, 2450001},
    {2000,  1,  1, 6, 730120 - EPOCH_OFFSET, 2451545},
    {2010,  1,  1, 5, 733773 - EPOCH_OFFSET, 2455198},
    {2020,  1,  1, 3, 737425 - EPOCH_OFFSET, 2458850},
    {2030,  1,  1, 2, 741078 - EPOCH_OFFSET, 2462503},
    {2040,  1,  1, 7, 744730 - EPOCH_OFFSET, 2466155},
    {2050,  1,  1, 6, 748383 - EPOCH_OFFSET, 2469808},
    {2132,  8, 31, 7, 778575 - EPOCH_OFFSET, 2500000},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_ymd(t.y, t.m, t.d);
            cmp_ok(got, "==", t.dt, "dt_from_ymd(%d, %d, %d)", t.y, t.m, t.d);
        }

        {
            dt_t got = dt_from_cjdn(t.cjdn);
            cmp_ok(got, "==", t.dt, "dt_from_cjdn(%d)", t.cjdn);
        }

        {
            int got = dt_cjdn(t.dt);
            cmp_ok(got, "==", t.cjdn, "dt_cjdn(%d)", t.dt);
        }

        {
            int y, m, d;
            dt_to_ymd(t.dt, &y, &m, &d);
            if (!ok((y == t.y && m == t.m && d == t.d), "dt_to_ymd(%d)", t.dt)) {
                diag("      got: %.4d-%.2d-%.2d", y, m, d);
                diag("      exp: %.4d-%.2d-%.2d", t.y, t.m, t.d);
            }
        }

        {
            int got = dt_year(t.dt);
            cmp_ok(got, "==", t.y, "dt_year(%d)", t.dt);
        }

        {
            int got = dt_month(t.dt);
            cmp_ok(got, "==", t.m, "dt_month(%d)", t.dt);
        }

        {
            int got = dt_day(t.dt);
            cmp_ok(got, "==", t.d, "dt_day(%d)", t.dt);
        }

        {
            int got = dt_day_of_week(t.dt);
            cmp_ok(got, "==", t.dow, "dt_day_of_week(%d)", t.dt);
        }

        {
            ok(dt_valid_ymd(t.y, t.m, t.d), "dt_valid_ymd(%d, %d, %d)", t.y, t.m, t.d);
        }

    }
    done_testing();
}
