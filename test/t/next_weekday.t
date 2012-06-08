#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    s/\A \s* //x;
    next if /\A (?: \# | \z)/x;
    chomp;
    my ($y, $w, $d, $current, $ey, $ew, $ed) = split /,\s*/, $_;

    {
        my $dt = dt_from_ywd($y, $w, $d);
        my $exp = sprintf '%.4d-W%.2d-%d', $ey, $ew, $ed;
        my $got = sprintf '%.4d-W%.2d-%d', dt_to_ywd(dt_next_weekday($dt, $current));
        is($got, $exp, "dt_next_weekday($dt, $current)");
    }
}

done_testing;

__DATA__
2012, 10, 1, 1, 2012, 10, 1
2012, 10, 2, 1, 2012, 10, 2
2012, 10, 3, 1, 2012, 10, 3
2012, 10, 4, 1, 2012, 10, 4
2012, 10, 5, 1, 2012, 10, 5
2012, 10, 6, 1, 2012, 11, 1
2012, 10, 7, 1, 2012, 11, 1
2012, 10, 1, 0, 2012, 10, 2
2012, 10, 2, 0, 2012, 10, 3
2012, 10, 3, 0, 2012, 10, 4
2012, 10, 4, 0, 2012, 10, 5
2012, 10, 5, 0, 2012, 11, 1
2012, 10, 6, 0, 2012, 11, 1
2012, 10, 7, 0, 2012, 11, 1
