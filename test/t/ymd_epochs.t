#!perl
use strict;
use warnings;

use Test::More 0.88;
use dtp qw[:all];

while (<DATA>) {
    chomp;
    s/\A \s* //x;
    s/\s* \# .* \z//x;
    next if /\A (?: \# | \z)/x;

    my ($y, $m, $d, $dt) = split /,\s*/, $_;
    {
        my $got = dt_from_ymd($y, $m, $d);
        is($got, $dt, "dt_from_ymd($y, $m, $d)");
    }

    {
        my $got = sprintf '%.4d-%.2d-%.2d', dt_to_ymd($dt);
        my $exp = sprintf '%.4d-%.2d-%.2d', $y, $m, $d;
        is($got, $exp, "dt_to_ymd($dt)");
    }

    {
        my $got = dt_year($dt);
        is($got, $y, "dt_year($dt)");
    }

    {
        my $got = dt_month($dt);
        is($got, $m, "dt_month($dt)");
    }

    {
        my $got = dt_day_of_month($dt);
        is($got, $d, "dt_day_of_month($dt)");
    }

    {
        my $got = dt_delta_years(0, $dt);
        is($got, $y, "dt_delta_years(0, $dt)");
    }
}

done_testing;

__DATA__
# Epochs from Calendrical Calculations, Third Edition, Table 1.2
-4713, 11, 24,  -1721425 # Chronological Modified Julian Date
-3760,  9,  7,  -1373427 # Hebrew
-3113,  8, 11,  -1137142 # Mayan
-3101,  1, 23,  -1132959 # Hinu (Kali Yuga)
-2636,  2, 15,   -963099 # Chinese
 -746,  2, 18,   -272787 # Egyptian
 -127, 12,  7,    -46410 # Tibetan
    0, 12, 30,        -1 # Julian
    1,  1,  1,         1 # Gregorian
    8,  8, 27,      2796 # Ethiopic
  284,  8, 29,    103605 # Coptic
  552,  7, 13,    201443 # Armenian
  622,  3, 22,    226896 # Persian
  622,  7, 19,    227015 # Islamic
  632,  6, 19,    230638 # Zoroastrian
 1792,  9, 22,    654415 # French Revolutionary
 1844,  3, 21,    673222 # Bahá'í
 1858, 11, 17,    678576 # Modified Julian Day Number
# Test int32_t
-5879610, 6, 22, -2147483648 # INT32_MIN
 5879611, 7, 11,  2147483647 # INT32_MAX
