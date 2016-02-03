#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;

my $program=$ARGV[0];
my $tool=$ARGV[1]; #"cppcheck";
my $interestingness=$ARGV[2];#"./test_interest.sh";

for (1..1) {
    my $id=Time::HiRes::time();
    my $runDir="runs/run-$id";

    `mkdir $runDir`;
    `cp $program $runDir/$program`;
    `cp $interestingness $runDir/$interestingness`;

    `cd $runDir && time creduce --save-temps --print-diff $interestingness $program >> runlog.txt 2>&1`;
    `cd $runDir && rm -f $program.orig $interestingness`;

    `rm -fr /tmp/scan-build-2016-*`;
    `rm -fr /tmp/cc*`;
}
