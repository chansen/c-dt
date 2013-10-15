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
            dt_t got = dt_rdn(dt_from_ywd(t.y, t.w, t.d));
            cmp_ok(got, "==", t.rdn, "dt_rdn(dt_from_ywd(%d, %d, %d))", t.y, t.w, t.d);
        }

        {
            int y, w, d;
            dt_to_ywd(dt_from_rdn(t.rdn), &y, &w, &d);
            if (!ok((y == t.y && w == t.w && d == t.d), "dt_to_ywd(dt_from_rdn(%d))", t.rdn)) {
                diag("     got: %.4d-W%.2d-%d", y, w, d);
                diag("     exp: %.4d-W%.2d-%d", t.y, t.w, t.d);
            }
        }

        {
            int got = dt_woy(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.w, "dt_woy(dt_from_rdn(%d))", t.rdn);
        }

        {
            int got = dt_dow(dt_from_rdn(t.rdn));
            cmp_ok(got, "==", t.d, "dt_dow(dt_from_rdn(%d))", t.rdn);
        }

        {
            ok(dt_valid_ywd(t.y, t.w, t.d), "dt_valid_ywd(%d, %d, %d)", t.y, t.w, t.d);
        }

    }
    done_testing();
}
