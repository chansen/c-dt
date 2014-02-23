#include "dt.h"
#include "tap.h"

const struct test {
    int  y;
    bool leap;
} tests[] = {
   {  400, 1 },
   {  401, 0 },
   {  800, 1 },
   {  801, 0 },
   { 1200, 1 },
   { 1201, 0 },
   { 1600, 1 },
   { 1601, 0 },
   { 1700, 0 },
   { 1800, 0 },
   { 1900, 0 },
   { 2000, 1 },
   { 2004, 1 },
   { 2100, 0 }
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int got = dt_days_in_year(t.y);
            cmp_ok(got, "==", 365 + t.leap, "dt_days_in_year(%d)", t.y);
        }

        {
            int got = dt_leap_year(t.y);
            cmp_ok(got, "==", (int)t.leap, "dt_leap_year(%d)", t.y);
        }

        {
            int got = dt_length_of_year(dt_from_yd(t.y, 1));
            cmp_ok(got, "==", 365 + t.leap, "dt_length_of_year(%.4d-001)", t.y);
        }
    }
    done_testing();
}
