#!/usr/bin/perl
use strict;
use warnings;

sub encode {
    my ($string) = @_;
    my $v = 0;
    foreach my $c (split //, $string) {
        $v = ($v << 5) | ((ord($c) | 0x20) ^ 0x60);
    }
    return $v;
}

my %Universal = (
    GMT => 0,
    UTC => 0,
    UT  => 0,
);

my %Military = (
    A =>   1*60, B =>   2*60, C =>   3*60,
    D =>   4*60, E =>   5*60, F =>   6*60,
    G =>   7*60, H =>   8*60, I =>   9*60,
    K =>  10*60, L =>  11*60, M =>  12*60,

    N =>  -1*60, O =>  -2*60, P =>  -3*60,
    Q =>  -4*60, R =>  -5*60, S =>  -6*60,
    T =>  -7*60, U =>  -8*60, V =>  -9*60,
    W => -10*60, X => -11*60, Y => -12*60,

    Z => 0,
);

my %Rfc = (
    UT  => 0,
    UTC => 0,
    GMT => 0,
    EST => -5*60, EDT => -4*60,
    CST => -6*60, CDT => -5*60,
    MST => -7*60, MDT => -6*60,
    PST => -8*60, PDT => -7*60,
);

my %FlagName;

BEGIN {
    my %flags = (
        DT_ZONE_UTC       => 0x01,
        DT_ZONE_RFC       => 0x02,
        DT_ZONE_MILITARY  => 0x04,
        DT_ZONE_AMBIGUOUS => 0x08,
    );
    require constant; constant->import(\%flags);
    %FlagName = reverse %flags;
}

my $EntryRx = do {
    my $offset = '[+-] (?: [01][0-9] | [2][0-3]) [:] [0-5][0-9]';
    my $name   = '[A-Z][A-Za-z]{0,4}';
    qr< ($name) \s+ ($offset) (?: \s+ / \s+ ($offset))? \s+ #>xo
};

open(my $fh, '<:raw', 'tools/zone.txt')
  or die qq<Could not open 'tools/zone.txt' for reading: '$!'>;

my %Zone;

while (<$fh>) {
    next if /\A \s* \# /x;

    my ($name, $offset1, $offset2) = m< \A $EntryRx >x
      or die qq/Could not parse zone entry at line: $./;

    my $encoded = encode($name);
    my $offset  = 0;
    my $flags   = 0;

    if ($offset2) {
        $flags  = DT_ZONE_AMBIGUOUS;
    }
    else {
        my ($h, $m) = split /[:]/, $offset1;
        $offset = $h * 60 + $m;
    }

    if (exists $Zone{$encoded}) {
        $flags |= DT_ZONE_AMBIGUOUS;
        $offset = 0;
    }

    if (exists $Universal{$name}) {
        $flags |= DT_ZONE_UTC;
        $offset = 0;
    }

    if (exists $Military{$name}) {
        $flags |= DT_ZONE_MILITARY;
        $offset = $Military{$name};
    }

    if (exists $Rfc{$name}) {
        $flags |= DT_ZONE_RFC;
        $offset = $Rfc{$name};
    }

    $Zone{$encoded} = [$flags, $offset, $name];
}

printf "/* Automatically generated by tools/zone.pl */\n";
foreach my $encoded (sort { $a <=> $b } keys %Zone) {
    my ($flags, $offset, $name) = @{ $Zone{$encoded} };
    
    if ($flags != 0) {
        my @names;

        while ((my $flag = $flags & -$flags) != 0) {
            push @names, $FlagName{$flag} || die sprintf '0x%.8X', $flag;
            $flags &= ~$flag;
        }
        
        $flags = join '|', @names;
    }

    printf "DT_ZONE_ENTRY(0x%.8X, %4d, \"%s\", %s)\n",
      $encoded, $offset, $name, $flags;
}