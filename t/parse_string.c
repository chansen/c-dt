#include "dt.h"
#include "tap.h"
#include <string.h>

const struct good_t {
    int ey;
    int em;
    int ed;
    const char *str;
    size_t elen;
} good[] = {
    {2012, 12, 24, "20121224",       8 },
    {2012, 12, 24, "2012-12-24",    10 },
    {2012, 12, 24, "2012359",        7 },
    {2012, 12, 24, "2012-359",       8 },
    {2012, 12, 24, "2012W521",       8 },
    {2012, 12, 24, "2012-W52-1",    10 },
    {2012, 12, 24, "2012Q485",       8 },
    {2012, 12, 24, "2012-Q4-85",    10 },
};

const struct bad_t {
    const char *str;
} bad[] = {
    {"20121232"     },  /* Invalid day of month */
    {"2012-12-310"  },  /* Invalid day of month */
    {"2012-13-24"   },  /* Invalid month */
    {"2012367"      },  /* Invalid day of year */
    {"2012-000"     },  /* Invalid day of year */
    {"2012W533"     },  /* Invalid week of year */
    {"2012-W52-8"   },  /* Invalid day of week */
    {"2012Q495"     },  /* Invalid day of quarter */
    {"2012-Q5-85"   },  /* Invalid quarter */
    {"20123670"     },  /* Trailing digit */
    {"201212320"    },  /* Trailing digit */
    {"2012-12"      },  /* Reduced accuracy */
    {"2012-Q4"      },  /* Reduced accuracy */
    {"2012-Q42"     },  /* Invalid */
    {"2012-Q1-1"    },  /* Invalid day of quarter */
    {"2012Q--420"   },  /* Invalid */
    {"2012-Q-420"   },  /* Invalid */
    {"2012Q11"      },  /* Incomplete */
    {"2012Q1234"    },  /* Trailing digit */
    {"2012W12"      },  /* Incomplete */
    {"2012W1234"    },  /* Trailing digit */
    {"2012W-123"    },  /* Invalid */
    {"2012U1234"    },  /* Invalid */
    {"2012-1234"    },  /* Invalid */
    {"2012-X1234"   },  /* Invalid */
};

int 
main() {
    int i, ntests;

    ntests = sizeof(good) / sizeof(*good);
    for (i = 0; i < ntests; i++) {
        const struct good_t t = good[i];

        {
            dt_t got = 0, exp = 0;
            size_t glen;

            glen = dt_parse_string(t.str, strlen(t.str), &got);
            ok(glen == t.elen, "dt_parse_string(%s) size_t: %d", t.str, (int)glen);
            exp = dt_from_ymd(t.ey, t.em, t.ed);
            cmp_ok(got, "==", exp, "dt_parse_string(%s)", t.str);
        }
    }

    ntests = sizeof(bad) / sizeof(*bad);
    for (i = 0; i < ntests; i++) {
        const struct bad_t t = bad[i];

        {
            dt_t got = 0;
            size_t glen;

            glen = dt_parse_string(t.str, strlen(t.str), &got);
            ok(glen == 0, "dt_parse_string(%s) size_t: %d", t.str, (int)glen);
        }
    }
    done_testing();
}

