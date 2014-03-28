#!/usr/bin/perl
# Copyright (c) 2012-2014 Christian Hansen <chansen@cpan.org>
# <https://github.com/chansen/c-dt>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met: 
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer. 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution. 
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This script computes the matrices that are used in dt_weekday.c
#
use strict;
use warnings;

my @DoW          = qw(M  T  W  T  F  S  S);
my @WeekDay      =   (1, 1, 1, 1, 1, 0, 0);
my $WeekDayCount = grep { $_ == 1 } @WeekDay;

(@WeekDay == 7)
  or die q/@WeekDay must contain 7 elements/;

(!grep { $_ > 1 || $_ < 0 } @WeekDay)
  or die q/Elements of @WeekDay must be either 1 or 0/;

($WeekDayCount > 0)
  or die q/$WeekDayCount must be > 0/;

sub delta_matrix {
    @_ == 1 || die q/Usage: delta_matrix($inclusive)/;
    my ($inclusive) = @_;

    my @T;
    for my $d1 (0..6) {
        for my $d2 (0..6) {
            my $c;
            if ($d1 <= $d2) {
                $c = $inclusive ? $WeekDay[$d1] : 0;
                for (; $d1 < $d2; $d2--) {
                    $c += $WeekDay[$d2];
                }
            }
            else {
                $c = $WeekDayCount + ($inclusive ? $WeekDay[$d2] : 0);
                for (; $d1 > $d2; $d2++) {
                    $c -= $WeekDay[$d2];
                }
            }
            push @T, $c;
        }
    }

    (@T == 7*7)
      or die q/@T != 7*7/;

    return @T;
}

sub add_matrix {
    @_ == 1 || die q/Usage: add_matrix($direction)/;
    my ($direction) = @_;

    ($direction == 1 || $direction == -1)
      or die q/Parameter 'direction' must be -1 or +1/;

    my @T;
    for my $d1 (0..6) {
        my ($c, $d2);

        $c  = 0;
        $d2 = $d1;
        while (!$WeekDay[$d2]) {
            $c--;
            $d2 = ($d1 + $c * $direction) % 7;
        }
        push @T, $c;
        for ($c = 1, my $i = 1; $i < $WeekDayCount; $i++, $c++) {
            $d2 = ($d1 + $c * $direction) % 7;
            while (!$WeekDay[$d2]) {
                $c++;
                $d2 = ($d1 + $c * $direction) % 7;
            }
            push @T, $c;
        }
    }

    (@T == 7*$WeekDayCount)
      or die q/@T != 7*$WeekDayCount/;

    return @T;
}

sub move_matrix {
    @_ == 1 || die q/Usage: move_matrix($direction)/;
    my ($direction) = @_;

    ($direction == 1 || $direction == -1)
      or die q/Parameter 'direction' must be -1 or +1/;

    my @T;
    for my $current (0, 1) {
        push @T, 0;
        for my $d1 (0..6) {
            my ($c, $d2);
            $c  = 1 * !$current;
            $d2 = ($d1 + $c * $direction) % 7;
            while (!$WeekDay[$d2]) {
                $c++;
                $d2 = ($d1 + $c * $direction) % 7;
            }
            push @T, $c;
        }
    }

    (@T == 8*2)
      or die q/@T != 8*2/;

    return @T;
}

my @T;

print "\n# dt_delta_workdays()\n\n";
@T = delta_matrix(0);
printf "/*      %s  (exclusive) */\n", join ' ', @DoW;
for (0..6) {
    printf "/* %s */ %s,\n", $DoW[$_], join ',', splice(@T, 0, 7);
}

@T = delta_matrix(1);
printf "/*      %s  (inclusive) */\n", join ' ', @DoW;;
for (0..6) {
    printf "/* %s */ %s,\n", $DoW[$_], join ',', splice(@T, 0, 7);
}

print "\n# dt_add_workdays()\n\n";
printf "/*       %s  (+n days) */\n", join ' ', 0..$WeekDayCount-1;
@T = add_matrix(+1);
for (0..6) {
    my @r = splice(@T, 0, $WeekDayCount);
    printf "/* %s */ %s,\n", $DoW[$_], join ',', sprintf('%2d', shift @r), @r;
}

printf "/*       %s  (-n days) */\n", join ' ', 0..$WeekDayCount-1;
@T = add_matrix(-1);
for (0..6) {
    my @r = splice(@T, 0, $WeekDayCount);
    printf "/* %s */ %s,\n", $DoW[$_], join ',', sprintf('%2d', shift @r), @r;
}

print "\n# dt_next_weekday()\n\n";
printf "/*  %s */\n", join ' ', @DoW;
@T = move_matrix(+1);
while (@T) {
    printf "{ %s },\n", join ',', splice(@T, 0, 8);
}

print "\n# dt_prev_weekday()\n\n";
printf "/*  %s */\n", join ' ', @DoW;
@T = move_matrix(-1);
while (@T) {
    printf "{ %s },\n", join ',', splice(@T, 0, 8);
}

