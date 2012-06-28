#define DT_INTERNAL
#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
    dt_t dt;
} tests[] = {
    /* Test cases from Calendrical Calculations, Third Edition, Table 1.2 */
#ifndef DT_T_UNSIGNED
    { -4713, 11, 24,  -1721425 - EPOCH_OFFSET }, /* Chronological Modified Julian Date */
    { -3760,  9,  7,  -1373427 - EPOCH_OFFSET }, /* Hebrew */
    { -3113,  8, 11,  -1137142 - EPOCH_OFFSET }, /* Mayan */
    { -3101,  1, 23,  -1132959 - EPOCH_OFFSET }, /* Hinu (Kali Yuga) */
    { -2636,  2, 15,   -963099 - EPOCH_OFFSET }, /* Chinese */
    {  -746,  2, 18,   -272787 - EPOCH_OFFSET }, /* Egyptian */
    {  -127, 12,  7,    -46410 - EPOCH_OFFSET }, /* Tibetan */
    {     0, 12, 30,        -1 - EPOCH_OFFSET }, /* Julian */
#endif
    {     1,  1,  1,         1 - EPOCH_OFFSET }, /* Gregorian */
    {     8,  8, 27,      2796 - EPOCH_OFFSET }, /* Ethiopic */
    {   284,  8, 29,    103605 - EPOCH_OFFSET }, /* Coptic */
    {   552,  7, 13,    201443 - EPOCH_OFFSET }, /* Armenian */
    {   622,  3, 22,    226896 - EPOCH_OFFSET }, /* Persian */
    {   622,  7, 19,    227015 - EPOCH_OFFSET }, /* Islamic */
    {   632,  6, 19,    230638 - EPOCH_OFFSET }, /* Zoroastrian */
    {  1792,  9, 22,    654415 - EPOCH_OFFSET }, /* French Revolutionary */
    {  1844,  3, 21,    673222 - EPOCH_OFFSET }, /* Bahá'í */
    {  1858, 11, 17,    678576 - EPOCH_OFFSET }, /* Modified Julian Day Number */
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
            ok(dt_valid_ymd(t.y, t.m, t.d), "dt_valid_ymd(%d, %d, %d)", t.y, t.m, t.d);
        }

    }
    done_testing();
}
