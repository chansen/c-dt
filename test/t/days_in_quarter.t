#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    s/\A \s* //x;
    next if /\A (?: \# | \z)/x;
    chomp;
    my ($y, $q, $exp) = split /,\s*/, $_;

    {
        my $got = dt_days_in_quarter($y, $q);
        is($got, $exp, "dt_days_in_quarter($y, $q)");
    }
}

done_testing;

__DATA__
2100,  1, 90
2100,  2, 91
2100,  3, 92
2100,  4, 92
2000,  1, 91
2000,  2, 91
2000,  3, 92
2000,  4, 92
# out of range
2000,  5,  0
2000,  0,  0
2000, -1,  0
2000, 10,  0
