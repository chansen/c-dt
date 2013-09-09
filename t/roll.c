#include "dt.h"
#include "tap.h"

const struct ymd {
    int y;
    int m;
    int d;
} days[] = {
    {2013,  1,  1}, /* Tuesday, Nyårsdagen (New Year's Day) */
    {2013,  3, 29}, /* Friday, Långfredagen (Good Friday) */
    {2013,  4,  1}, /* Monday, Annandag påsk (Easter Monday) */
    {2013,  5,  1}, /* Wednesday, Första maj (First of May) */
    {2013,  5,  9}, /* Thursday, Kristi himmelsfärds dag (Ascension Day) */
    {2013,  6,  6}, /* Thursday, Sveriges nationaldag (National Day of Sweden) */
    {2013,  6, 21}, /* Friday, Midsommarafton (Midsummer's Eve) */
    {2013, 12, 24}, /* Tuesday, Julafton (Christmas Eve) */
    {2013, 12, 25}, /* Wednesday, Juldagen (Christmas Day) */
    {2013, 12, 26}, /* Thursday, Annandag jul (Boxing Day) */
    {2013, 12, 31}, /* Tuesday, Nyårsafton (New Year's Eve) */
};

const struct test {
    int y;
    int m;
    int d; 
    dt_bdc_t convention;
    int ey;
    int em;
    int ed;
} tests[] = {
    {2013, 12, 23, DT_FOLLOWING,            2013, 12, 23},
    {2013, 12, 23, DT_MODIFIED_FOLLOWING,   2013, 12, 23},
    {2013, 12, 24, DT_FOLLOWING,            2013, 12, 27},
    {2013, 12, 24, DT_MODIFIED_FOLLOWING,   2013, 12, 27},
    {2013, 12, 30, DT_FOLLOWING,            2013, 12, 30},
    {2013, 12, 30, DT_MODIFIED_FOLLOWING,   2013, 12, 30},
    {2013, 12, 31, DT_FOLLOWING,            2014,  1,  1},
    {2013, 12, 31, DT_MODIFIED_FOLLOWING,   2013, 12, 30},
    {2013,  1,  1, DT_PRECEDING,            2012, 12, 31},
    {2013,  1,  1, DT_MODIFIED_PRECEDING,   2013,  1,  2},
    {2013,  1,  2, DT_PRECEDING,            2013,  1,  2},
    {2013,  1,  2, DT_MODIFIED_PRECEDING,   2013,  1,  2},
    {2013,  4,  1, DT_PRECEDING,            2013,  3, 28},
    {2013,  4,  1, DT_MODIFIED_PRECEDING,   2013,  4,  2},
};

int
main() {
    int ntests, nholidays;
    int i;
    dt_t holidays[20];

    nholidays = sizeof(days) / sizeof(*days);
    for (i = 0; i < nholidays; i++) {
        const struct ymd date = days[i];
        holidays[i] = dt_from_ymd(date.y, date.m, date.d);
    }

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t src = dt_from_ymd(t.y, t.m, t.d);
            dt_t got = dt_roll(src, t.convention, holidays, nholidays);
            dt_t exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_roll(%.4d-%.2d-%.2d, %d)", 
              t.y, t.m, t.d, t.convention);
        }
    }
    done_testing();
}

