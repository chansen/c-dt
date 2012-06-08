#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    s/\A \s* //x;
    next if /\A (?: \# | \z)/x;
    chomp;
    my ($y, $m, $exp) = split /,\s*/, $_;

    {
        my $got = dt_days_in_month($y, $m);
        is($got, $exp, "dt_days_in_month($y, $m)");
    }
}

done_testing;

__DATA__
2100,  1, 31
2100,  2, 28
2100,  3, 31
2100,  4, 30
2100,  5, 31
2100,  6, 30
2100,  7, 31
2100,  8, 31
2100,  9, 30
2100, 10, 31
2100, 11, 30
2100, 12, 31
2000,  1, 31
2000,  2, 29
2000,  3, 31
2000,  4, 30
2000,  5, 31
2000,  6, 30
2000,  7, 31
2000,  8, 31
2000,  9, 30
2000, 10, 31
2000, 11, 30
2000, 12, 31
# out of range
2000, 13,  0
2000,  0,  0
2000, -1,  0
2000, 50,  0
