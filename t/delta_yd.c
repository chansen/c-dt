#include "dt.h"
#include "tap.h"

const struct test {
    int y1;
    int d1;
    int y2;
    int d2;
    int ny;
    int nd;
} tests[] = {
    {2010,   1, 2010,   1,   0,    0},
    {2010,   1, 2010,   2,   0,    1},
    {2010,   1, 2010,  31,   0,   30},
    {2010,   1, 2010,  32,   0,   31},
    {2010,   1, 2010,  59,   0,   58},
    {2010,   1, 2010,  60,   0,   59},
    {2010,   1, 2010, 365,   0,  364},
    {2010,   1, 2011,   1,   1,    0},
    {2010,   1, 2011, 365,   1,  364},
    {2010,   1, 2012,   1,   2,    0},
    {2010,  10, 2010,   1,   0,   -9},
    {2010,  10, 2010,   2,   0,   -8},
    {2010,  10, 2010,   9,   0,   -1},
    {2010,  10, 2010,  10,   0,    0},
    {2010,  10, 2010,  11,   0,    1},
    {2010,  10, 2010,  31,   0,   21},
    {2010,  10, 2010,  32,   0,   22},
    {2010,  10, 2010,  40,   0,   30},
    {2010,  10, 2010,  41,   0,   31},
    {2010,  10, 2010,  59,   0,   49},
    {2010,  10, 2010,  60,   0,   50},
    {2010,  10, 2010,  68,   0,   58},
    {2010,  10, 2010,  69,   0,   59},
    {2010,  10, 2010, 365,   0,  355},
    {2010,  10, 2011,   1,   0,  356},
    {2010,  10, 2011,   9,   0,  364},
    {2010,  10, 2011,  10,   1,    0},
    {2010,  89, 2011, 121,   1,   32},
    {2010, 120, 2011, 121,   1,    1},
    {2010,  59, 2012,  58,   1,  364},
    {2010,  59, 2012,  59,   2,    0},
    {2010,  59, 2012,  60,   2,    1},
    {2012,  59, 2014,  58,   1,  364},
    {2012,  59, 2014,  59,   2,    0},
    {2012,  59, 2014,  60,   2,    1},
    {2012,  60, 2014,  59,   1,  364},
    {2012,  60, 2014,  60,   2,    0},
    {2012,  60, 2014,  61,   2,    1},
    {2012,  60, 2016,  59,   3,  364},
    {2012,  60, 2016,  60,   4,    0},
    {2012,  60, 2016,  61,   4,    1},
    {2010,   1, 2009, 365,   0,   -1},
    {2010,   1, 2009, 364,   0,   -2},
    {2010,   1, 2009, 336,   0,  -30},
    {2010,   1, 2009, 335,   0,  -31},
    {2010,   1, 2009, 334,   0,  -32},
    {2010,   1, 2009, 306,   0,  -60},
    {2010,   1, 2009, 305,   0,  -61},
    {2010,   1, 2009,   2,   0, -364},
    {2010,   1, 2009,   1,  -1,    0},
    {2010,  15, 2010,  15,   0,    0},
    {2010,  15, 2010,  14,   0,   -1},
    {2010,  15, 2010,   1,   0,  -14},
    {2010,  15, 2009, 365,   0,  -15},
    {2010,  15, 2009, 350,   0,  -30},
    {2010,  15, 2009, 349,   0,  -31},
    {2010,  15, 2009, 348,   0,  -32},
    {2010,  59, 2009,  60,   0, -364},
    {2010,  59, 2009,  59,  -1,    0},
    {2010,  59, 2009,  58,  -1,   -1},
    {2010,  59, 2008,  60,  -1, -365},
    {2010,  59, 2008,  59,  -2,    0},
    {2010,  59, 2008,  58,  -2,   -1},
    {2012,  60, 2009,  60,  -3,    0},
    {2012,  60, 2009,  59,  -3,   -1},
    {2012,  60, 2009,  58,  -3,   -2},
    {2012,  60, 2008,  61,  -3, -365},
    {2012,  60, 2008,  60,  -4,    0},
    {2012,  60, 2008,  59,  -4,   -1},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            int ny, nd;
            dt_t dt1 = dt_from_yd(t.y1, t.d1);
            dt_t dt2 = dt_from_yd(t.y2, t.d2);

            dt_delta_yd(dt1, dt2, &ny, &nd);
            if (!ok((ny == t.ny && nd == t.nd),
                "dt_delta_yd(%.4d-%.3d, %.4d-%.3d)", t.y1, t.d1, t.y2, t.d2)) {
                diag("      got: Y:%d, D:%d", ny, nd);
                diag("      exp: Y:%d, D:%d", t.ny, t.nd);
            }
        }
    }
    done_testing();
}

