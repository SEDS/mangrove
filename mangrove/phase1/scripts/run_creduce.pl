#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;
use File::Slurp qw(read_file write_file);

my $workDir = $ARGV[0];
my $testScript_gen = "test_interest_gen.sh";
my $testScript = "test_interest.sh";
my $flags="--save-temps --no-default-passes --add-pass pass_includes 0 0 --add-pass pass_blank 0 1 --add-pass pass_clang_binsrch remove-unused-function 3 --add-pass pass_clang_binsrch replace-function-def-with-decl 33 --add-pass pass_clang remove-namespace 200 --add-pass pass_clang remove-unused-function 220 --add-pass pass_clang return-void 212 --add-pass pass_clang remove-unused-var 223 --add-pass pass_unifdef 0 450 --add-pass pass_comments 0 451";
my %warnings = ();
my $keepNextLine=0;

my $logFile="~/creduce.log";
`cd $workDir && creduce $flags ./a_$testScript $fileName >> $logFile 2>&1`;
`cd $workDir && creduce $flags ./a_$testScript $fileName >> $logFile 2>&1`;
`cd $workDir && creduce $flags ./a_$testScript $fileName >> $logFile 2>&1`;