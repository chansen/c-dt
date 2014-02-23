#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int m;
    int d;
} tests[] = {
   { 2100,  1, 31 },
   { 2100,  2, 28 },
   { 2100,  3, 31 },
   { 2100,  4, 30 },
   { 2100,  5, 31 },
   { 2100,  6, 30 },
   { 2100,  7, 31 },
   { 2100,  8, 31 },
   { 2100,  9, 30 },
   { 2100, 10, 31 },
   { 2100, 11, 30 },
   { 2100, 12, 31 },
   { 2000,  1, 31 },
   { 2000,  2, 29 },
   { 2000,  3, 31 },
   { 2000,  4, 30 },
   { 2000,  5, 31 },
   { 2000,  6, 30 },
   { 2000,  7, 31 },
   { 2000,  8, 31 },
   { 2000,  9, 30 },
   { 2000, 10, 31 },
   { 2000, 11, 30 },
   { 2000, 12, 31 },
   { 2000, 13,  0 },
   { 2000,  0,  0 },
   { 2000, -1,  0 },
   { 2000, 50,  0 },
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int got = dt_days_in_month(t.y, t.m);
            cmp_ok(got, "==", t.d, "dt_days_in_month(%d, %d)", t.y, t.m);
        }

        if (t.d != 0) {
            int got = dt_length_of_month(dt_from_ymd(t.y, t.m, 1));
            cmp_ok(got, "==", t.d, "dt_length_of_month(%.4d-%.2d-01)", t.y, t.m);
        }
    }
    done_testing();
}
