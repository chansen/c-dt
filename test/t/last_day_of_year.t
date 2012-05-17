#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    next if /\A \# /x;
    chomp;
    my ($y, $m, $d, $delta, $ey) = split /,\s*/, $_;

    {
        my $dt = dt_from_ymd($y, $m, $d);
        my $exp = sprintf '%.4d-%.2d-%.2d', $ey, 12, 31;
        my $got = sprintf '%.4d-%.2d-%.2d', dt_to_ymd(dt_last_day_of_year($dt, $delta));
        is($got, $exp, "dt_last_day_of_year($dt, $delta)");
    }

    {
        my $dt1 = dt_from_ymd($y, $m, $d);
        my $dt2 = dt_last_day_of_year($dt1, $delta);
        my $got = dt_delta_years($dt1, $dt2);
        is($got, $delta, sprintf '%.4d -- %.4d', $y, $ey);
    }
}

done_testing;

__DATA__
2000,  7,  8,  21, 2021
2001, 12, 24, -14, 1987
2002,  3,  4,  21, 2023
2003,  1,  8, -24, 1979
2004,  8, 13,  -3, 2001
2005,  4,  7,   2, 2007
2006,  4,  4,  -7, 1999
2007,  2, 12,  10, 2017
2008,  8, 17,  -9, 1999
2009, 10,  1, -13, 1996
2010, 12, 21,  -4, 2006
2011, 10, 29,   7, 2018
2012,  7, 24,   8, 2020
2013,  7, 31, -18, 1995
2014,  3, 17,  16, 2030
2015,  5,  8,  -2, 2013
2016,  4, 14,  14, 2030
2017,  3, 18, -17, 2000
2018, 12,  9,  -9, 2009
2019,  5,  6, -10, 2009
2020,  6,  1,   0, 2020
