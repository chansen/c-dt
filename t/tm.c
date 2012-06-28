#include <string.h>
#define DT_INTERNAL
#include "dt.h"
#include "tap.h"

const struct test {
    int year;
    int mon;
    int mday;
    int wday;
    int yday;
    dt_t dt;
} tests[] = {
    { 70,  0,  1, 4,   0, 719163 - EPOCH_OFFSET},
    {110, 11, 31, 5, 364, 734137 - EPOCH_OFFSET},
    {120, 11, 31, 4, 365, 737790 - EPOCH_OFFSET},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            struct tm tm;
            dt_t dt;

            memset(&tm, 0, sizeof(tm));
            tm.tm_year = t.year;
            tm.tm_mon  = t.mon;
            tm.tm_mday = t.mday;
            dt = dt_from_struct_tm(&tm);
            cmp_ok(dt, "==", t.dt, "dt_from_struct_tm(tm->tm_year: %d, tm->tm_mon: %d, tm->tm_mday: %d)", 
              tm.tm_year, tm.tm_mon, tm.tm_mday);
        }

        {
            struct tm tm;

            memset(&tm, 0, sizeof(tm));
            dt_to_struct_tm(t.dt, &tm);
            cmp_ok(tm.tm_year, "==", t.year, "dt_to_struct_tm(%d, &tm) tm_year", t.dt);
            cmp_ok(tm.tm_mon, "==", t.mon, "dt_to_struct_tm(%d, &tm) tm_mon", t.dt);
            cmp_ok(tm.tm_mday, "==", t.mday, "dt_to_struct_tm(%d, &tm) tm_mday", t.dt);
            cmp_ok(tm.tm_wday, "==", t.wday, "dt_to_struct_tm(%d, &tm) tm_wday", t.dt);
            cmp_ok(tm.tm_yday, "==", t.yday, "dt_to_struct_tm(%d, &tm) tm_yday", t.dt);
        }
    }
    done_testing();
}
