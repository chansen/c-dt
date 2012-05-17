#!perl
use strict;
use warnings;

use File::Copy          qw[copy];
use ExtUtils::MakeMaker qw[WriteMakefile];

copy('../dt.c', 'dt.c')
  or die qq<Couldn't copy '../dt.c' to 'dt.c': '$!'>;

copy('../dt.h', 'dt.h')
  or die qq<Couldn't copy '../dt.h' to 'dt.h': '$!'>;

WriteMakefile(
    'NAME'         => 'dtp',
    'VERSION_FROM' => 'dtp.pm',
    'OBJECT'       => '$(O_FILES)',
    'clean'        => { FILES => '$(O_FILES) dt.c dt.h' },
    'PREREQ_PM'    => {
        'Test::More' => '0.88',
    },
);

sub MY::install { "install ::\n" };

