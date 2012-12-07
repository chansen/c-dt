#include <string.h>
#include "dt.h"
#include "tap.h"

const struct test {
    int year;
    int mon;
    int mday;
    int wday;
    int yday;
    int rdn;
} tests[] = {
    { 70,  0,  1, 4,   0, 719163},
    {110, 11, 31, 5, 364, 734137},
    {120, 11, 31, 4, 365, 737790},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            struct tm tm;
            int rdn;

            memset(&tm, 0, sizeof(tm));
            tm.tm_year = t.year;
            tm.tm_mon  = t.mon;
            tm.tm_mday = t.mday;
            rdn = dt_rdn(dt_from_struct_tm(&tm));
            cmp_ok(rdn, "==", t.rdn, "dt_rdn(dt_from_struct_tm(tm->tm_year: %d, tm->tm_mon: %d, tm->tm_mday: %d))", 
              tm.tm_year, tm.tm_mon, tm.tm_mday);
        }

        {
            struct tm tm;

            memset(&tm, 0, sizeof(tm));
            dt_to_struct_tm(dt_from_rdn(t.rdn), &tm);
            cmp_ok(tm.tm_year, "==", t.year, "dt_to_struct_tm(dt_from_rdn(%d), &tm) tm_year", t.rdn);
            cmp_ok(tm.tm_mon, "==", t.mon, "dt_to_struct_tm(dt_from_rdn(%d), &tm) tm_mon", t.rdn);
            cmp_ok(tm.tm_mday, "==", t.mday, "dt_to_struct_tm(dt_from_rdn(%d), &tm) tm_mday", t.rdn);
            cmp_ok(tm.tm_wday, "==", t.wday, "dt_to_struct_tm(dt_from_rdn(%d), &tm) tm_wday", t.rdn);
            cmp_ok(tm.tm_yday, "==", t.yday, "dt_to_struct_tm(dt_from_rdn(%d), &tm) tm_yday", t.rdn);
        }
    }
    done_testing();
}
