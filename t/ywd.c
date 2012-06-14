#include "dt.h"
#include "tap.h"
#include "ywd.h"

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_ywd(t.y, t.w, t.d);
            cmp_ok(got, "==", t.dt, "dt_from_ywd(%d, %d, %d)", t.y, t.w, t.d);
        }

        {
            int y, w, d;
            dt_to_ywd(t.dt, &y, &w, &d);
            if (!ok((y == t.y && w == t.w && d == t.d), "dt_to_ywd(%d)", t.dt)) {
                diag("     got: %.4d-W%.2d-%d", y, w, d);
                diag("     exp: %.4d-W%.2d-%d", t.y, t.w, t.d);
            }
        }

        {
            int got = dt_week(t.dt);
            cmp_ok(got, "==", t.w, "dt_week(%d)", t.dt);
        }

        {
            int got = dt_day_of_week(t.dt);
            cmp_ok(got, "==", t.d, "dt_day_of_week(%d)", t.dt);
        }

        {
            ok(dt_valid_ywd(t.y, t.w, t.d), "dt_valid_ywd(%d, %d, %d)", t.y, t.w, t.d);
        }

    }
    done_testing();
}
