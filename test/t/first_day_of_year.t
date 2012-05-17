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
        my $exp = sprintf '%.4d-%.2d-%.2d', $ey, 1, 1;
        my $got = sprintf '%.4d-%.2d-%.2d', dt_to_ymd(dt_first_day_of_year($dt, $delta));
        is($got, $exp, "dt_to_ymd(dt_first_day_of_year($dt, $delta))");
    }

    {
        my $dt1 = dt_from_ymd($y, $m, $d);
        my $dt2 = dt_first_day_of_year($dt1, $delta);
        my $got = dt_delta_years($dt1, $dt2);
        is($got, $delta, sprintf '%.4d-%.2d-%.2d -- %.4d-%.2d-%.2d', $y, $m, $d, $ey, 1, 1);
    }
}

done_testing;

__DATA__
2000,  2, 15, -19, 1981
2001,  7, 27, -10, 1991
2002,  6,  3,  14, 2016
2003,  7, 12, -21, 1982
2004,  8,  4,   9, 2013
2005,  5, 15, -24, 1981
2006,  4, 11,   3, 2009
2007,  5,  5, -11, 1996
2008, 11, 30,   3, 2011
2009, 12, 16,   1, 2010
2010, 10, 26, -20, 1990
2011,  2, 28,  17, 2028
2012, 11, 12,  -5, 2007
2013, 11,  3, -20, 1993
2014,  7, 29,  16, 2030
2015,  6,  8,   2, 2017
2016, 11,  9, -22, 1994
2017,  6, 10,   2, 2019
2018,  1, 20, -20, 1998
2019,  3, 28,   0, 2019
2020, 11, 15,  19, 2039
