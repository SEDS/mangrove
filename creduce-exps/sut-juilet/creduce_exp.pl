#!/usr/bin/perl

use strict;
use 5.014;
use warnings;

my $program=$ARGV[0]; # sample.c
my $interestingness=$ARGV[1];#"./test_interest.sh";

for (1..10) {
    my $id=Time::HiRes::time();
    my $runDir="runs/run-$id";

    `mkdir $runDir`;
    `cp $program $runDir/$program`;
    `cp $interestingness $runDir/$interestingness`;

    `cd $runDir && time creduce $interestingness $program >> runlog.txt 2>&1`;
    `cd $runDir && rm -f $program.orig $interestingness`;

   `rm -fr /tmp/scan-build-2016-*`; #update according to evnironment
}
