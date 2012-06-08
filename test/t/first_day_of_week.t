#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    s/\A \s* //x;
    next if /\A (?: \# | \z)/x;
    chomp;
    my ($y, $w, $d, $dow, $ey, $ew, $ed) = split /,\s*/, $_;

    {
        my $dt = dt_from_ywd($y, $w, $d);
        my $exp = sprintf '%.4d-W%.2d-%d', $ey, $ew, $ed;
        my $got = sprintf '%.4d-W%.2d-%d', dt_to_ywd(dt_first_day_of_week($dt, $dow));
        is($got, $exp, "dt_first_day_of_week($dt, $dow)");
    }
}

done_testing;

__DATA__
2012, 10, 7, 1, 2012, 10, 1
2012, 10, 7, 2, 2012, 10, 2
2012, 10, 7, 3, 2012, 10, 3
2012, 10, 7, 4, 2012, 10, 4
2012, 10, 7, 5, 2012, 10, 5
2012, 10, 7, 6, 2012, 10, 6
2012, 10, 7, 7, 2012, 10, 7
2012, 11, 1, 7, 2012, 10, 7
2012, 10, 1, 1, 2012, 10, 1
2012, 10, 2, 2, 2012, 10, 2
2012, 10, 3, 3, 2012, 10, 3
2012, 10, 4, 4, 2012, 10, 4
2012, 10, 5, 5, 2012, 10, 5
2012, 10, 6, 6, 2012, 10, 6
2012, 10, 7, 7, 2012, 10, 7
