#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
    int rdn;
} tests[] = {
    /* Test cases from Calendrical Calculations, Third Edition, Table 1.2 */
    { -4713, 11, 24,  -1721425 }, /* Chronological Modified Julian Date */
    { -3760,  9,  7,  -1373427 }, /* Hebrew */
    { -3113,  8, 11,  -1137142 }, /* Mayan */
    { -3101,  1, 23,  -1132959 }, /* Hinu (Kali Yuga) */
    { -2636,  2, 15,   -963099 }, /* Chinese */
    {  -746,  2, 18,   -272787 }, /* Egyptian */
    {  -127, 12,  7,    -46410 }, /* Tibetan */
    {     0, 12, 30,        -1 }, /* Julian */
    {     1,  1,  1,         1 }, /* Gregorian */
    {     8,  8, 27,      2796 }, /* Ethiopic */
    {   284,  8, 29,    103605 }, /* Coptic */
    {   552,  7, 13,    201443 }, /* Armenian */
    {   622,  3, 22,    226896 }, /* Persian */
    {   622,  7, 19,    227015 }, /* Islamic */
    {   632,  6, 19,    230638 }, /* Zoroastrian */
    {  1792,  9, 22,    654415 }, /* French Revolutionary */
    {  1844,  3, 21,    673222 }, /* Bahá'í */
    {  1858, 11, 17,    678576 }, /* Modified Julian Day Number */
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int rdn = dt_rdn(dt_from_ymd(t.y, t.m, t.d));
            cmp_ok(rdn, "==", t.rdn, "dt_rdn(dt_from_ymd(%d, %d, %d))", t.y, t.m, t.d);
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
            int got = dt_dom(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.d, "dt_dom(dt_from_rdn(%d))", t.rdn);
        }

        {
            ok(dt_valid_ymd(t.y, t.m, t.d), "dt_valid_ymd(%d, %d, %d)", t.y, t.m, t.d);
        }

    }
    done_testing();
}
