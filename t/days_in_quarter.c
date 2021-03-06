#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int q;
    int d;
} tests[] = {
    { 2100,  1, 90 },
    { 2100,  2, 91 },
    { 2100,  3, 92 },
    { 2100,  4, 92 },
    { 2000,  1, 91 },
    { 2000,  2, 91 },
    { 2000,  3, 92 },
    { 2000,  4, 92 },
    { 2000,  5,  0 },
    { 2000,  0,  0 },
    { 2000, -1,  0 },
    { 2000, 10,  0 },
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int got = dt_days_in_quarter(t.y, t.q);
            cmp_ok(got, "==", t.d, "dt_days_in_quarter(%d, %d)", t.y, t.q);
        }

        if (t.d != 0) {
            int got = dt_length_of_quarter(dt_from_yqd(t.y, t.q, 1));
            cmp_ok(got, "==", t.d, "dt_length_of_quarter(%.4d-Q%d-01)", t.y, t.q);
        }
    }
    done_testing();
}
