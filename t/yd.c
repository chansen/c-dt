#define DT_INTERNAL
#include "dt.h"
#include "tap.h"

const struct test {
    int y;
    int d;
    dt_t dt;
} tests[] = {
    {1970, 195, 719357 - EPOCH_OFFSET},
    {1971, 256, 719783 - EPOCH_OFFSET},
    {1972, 199, 720091 - EPOCH_OFFSET},
    {1973, 331, 720589 - EPOCH_OFFSET},
    {1974, 249, 720872 - EPOCH_OFFSET},
    {1975,  30, 721018 - EPOCH_OFFSET},
    {1976, 300, 721653 - EPOCH_OFFSET},
    {1977, 217, 721936 - EPOCH_OFFSET},
    {1978, 114, 722198 - EPOCH_OFFSET},
    {1979,  38, 722487 - EPOCH_OFFSET},
    {1980, 278, 723092 - EPOCH_OFFSET},
    {1981, 300, 723480 - EPOCH_OFFSET},
    {1982,  58, 723603 - EPOCH_OFFSET},
    {1983, 222, 724132 - EPOCH_OFFSET},
    {1984, 185, 724460 - EPOCH_OFFSET},
    {1985, 324, 724965 - EPOCH_OFFSET},
    {1986,  93, 725099 - EPOCH_OFFSET},
    {1987, 338, 725709 - EPOCH_OFFSET},
    {1988, 174, 725910 - EPOCH_OFFSET},
    {1989, 350, 726452 - EPOCH_OFFSET},
    {1990, 170, 726637 - EPOCH_OFFSET},
    {1991, 291, 727123 - EPOCH_OFFSET},
    {1992, 251, 727448 - EPOCH_OFFSET},
    {1993, 214, 727777 - EPOCH_OFFSET},
    {1994, 107, 728035 - EPOCH_OFFSET},
    {1995,  94, 728387 - EPOCH_OFFSET},
    {1996, 360, 729018 - EPOCH_OFFSET},
    {1997, 164, 729188 - EPOCH_OFFSET},
    {1998,  45, 729434 - EPOCH_OFFSET},
    {1999, 360, 730114 - EPOCH_OFFSET},
    {2000, 341, 730460 - EPOCH_OFFSET},
    {2001, 133, 730618 - EPOCH_OFFSET},
    {2002, 140, 730990 - EPOCH_OFFSET},
    {2003, 140, 731355 - EPOCH_OFFSET},
    {2004, 233, 731813 - EPOCH_OFFSET},
    {2005,  22, 731968 - EPOCH_OFFSET},
    {2006,  80, 732391 - EPOCH_OFFSET},
    {2007, 340, 733016 - EPOCH_OFFSET},
    {2008, 365, 733406 - EPOCH_OFFSET},
    {2009, 254, 733661 - EPOCH_OFFSET},
    {2010, 116, 733888 - EPOCH_OFFSET},
    {2011, 301, 734438 - EPOCH_OFFSET},
    {2012, 143, 734645 - EPOCH_OFFSET},
    {2013, 106, 734974 - EPOCH_OFFSET},
    {2014, 102, 735335 - EPOCH_OFFSET},
    {2015, 347, 735945 - EPOCH_OFFSET},
    {2016, 210, 736173 - EPOCH_OFFSET},
    {2017, 277, 736606 - EPOCH_OFFSET},
    {2018, 139, 736833 - EPOCH_OFFSET},
    {2019,  99, 737158 - EPOCH_OFFSET},
    {2020, 282, 737706 - EPOCH_OFFSET},
};

int 
main() {
    int i, ntests;

    ntests = sizeof(tests) / sizeof(*tests);
    for (i = 0; i < ntests; i++) {
        const struct test t = tests[i];

        {
            dt_t got = dt_from_yd(t.y, t.d);
            cmp_ok(got, "==", t.dt, "dt_from_yd(%d, %d)", t.y, t.d);
        }

        {
            int y, d;
            dt_to_yd(t.dt, &y, &d);
            if (!ok((y == t.y && d == t.d), "dt_to_yd(%d)", t.dt)) {
                diag("     got: %.4d-%.3d", y, d);
                diag("     exp: %.4d-%.3d", t.y, t.d);
            }
        }

        {
            int got = dt_year(t.dt);
            cmp_ok(got, "==", t.y, "dt_year(%d)", t.dt);
        }

        {
            int got = dt_day_of_year(t.dt);
            cmp_ok(got, "==", t.d, "dt_day_of_year(%d)", t.dt);
        }

        {
            ok(dt_valid_yd(t.y, t.d), "dt_valid_yd(%d, %d)", t.y, t.d);
        }

    }
    done_testing();
}
