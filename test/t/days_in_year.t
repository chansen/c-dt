#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    s/\A \s* //x;
    next if /\A (?: \# | \z)/x;
    chomp;
    my ($y, $is_leap) = split /,\s*/, $_;

    {
        my $got = dt_leap_year($y);
        my $exp = !!$is_leap;
        is($got, $exp, "dt_leap_year($y)");
    }

    {
        my $got = dt_days_in_year($y);
        my $exp = $is_leap ? 366 : 365;
        is($got, $exp, "dt_days_in_year($y)");
    }
}

done_testing;

__DATA__
 400, 1
 401, 0
 800, 1
 801, 0
1200, 1
1201, 0
1600, 1
1601, 0
1700, 0
1800, 0
1900, 0
2000, 1
2004, 1
2100, 0
