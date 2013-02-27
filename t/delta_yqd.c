#include "dt.h"
#include "tap.h"

const struct test {
    int y1;
    int q1;
    int d1;
    int y2;
    int q2;
    int d2;
    int ny;
    int nq;
    int nd;
} tests[] = {
    {2010, 1,  1, 2010, 1,  1,  0,   0,   0},
    {2010, 1,  1, 2010, 2,  1,  0,   1,   0},
    {2010, 1,  1, 2010, 2, 10,  0,   1,   9},
    {2012, 4, 92, 2016, 4, 92,  4,   0,   0},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int ny, nq, nd;
            dt_t dt1 = dt_from_yqd(t.y1, t.q1, t.d1);
            dt_t dt2 = dt_from_yqd(t.y2, t.q2, t.d2);

            dt_delta_yqd(dt1, dt2, &ny, &nq, &nd);
            if (!ok((ny == t.ny && nq == t.nq && nd == t.nd),
                "dt_delta_yqd(%.4d-Q%d-%.2d, %.4d-Q%d-%.2d)",
                 t.y1, t.q1, t.d1, t.y2, t.q2, t.d2)) {
                diag("      got: Y:%d, Q:%d, D:%d", ny, nq, nd);
                diag("      exp: Y:%d, Q:%d, D:%d", t.ny, t.nq, t.nd);
            }
        }

        {
            int nq, nd, eq;
            dt_t dt1 = dt_from_yqd(t.y1, t.q1, t.d1);
            dt_t dt2 = dt_from_yqd(t.y2, t.q2, t.d2);

            dt_delta_qd(dt1, dt2, &nq, &nd);
            eq = t.nq + (t.ny * 4);
            if (!ok((nq == eq && nd == t.nd),
                "dt_delta_md(%.4d-Q%d-%.2d, %.4d-Q%d-%.2d)",
                 t.y1, t.q1, t.d1, t.y2, t.q2, t.d2)) {
                diag("      got: Q:%d, D:%d", nq, nd);
                diag("      exp: Q:%d, D:%d", eq, t.nd);
            }
        }

        {
            int nq, eq;
            dt_t dt1 = dt_from_yqd(t.y1, t.q1, t.d1);
            dt_t dt2 = dt_from_yqd(t.y2, t.q2, t.d2);

            nq = dt_delta_quarters(dt1, dt2, 1);
            eq = t.nq + (t.ny * 4);
            cmp_ok(nq, "==", eq, "dt_delta_quarters(%.4d-Q%d-%.2d, %.4d-Q%d-%.2d, true)", 
              t.y1, t.q1, t.d1, t.y2, t.q2, t.d2);
        }
    }
    done_testing();
}

