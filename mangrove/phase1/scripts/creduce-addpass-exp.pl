#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;
use Math::BigFloat;

my $program="sample.c";
my $tool="scan-built";
my $interestingness="./run_script.sh";

my @passes = ();
#"pass_clang remove-unused-function 10", "pass_clang unify-function-decl 10", "pass_clex rm-tok-pattern-4 10", "pass_lines 0 10"

open ALL_PASSES,"<../all_passes.txt" or die $!;
while (my $line = <ALL_PASSES>){ push(@passes, $line); }
close ALL_PASSES;

my $size = scalar @passes;
print "tool,input,output,pass,time,label\n";
for(my $i=0; $i < $size; $i++){
   my $start = Time::HiRes::time();
   my $fileName=$passes[$i];
   $fileName=~ s/\n//g;
   my $pass = $fileName;
   $fileName=~ s/ /-/g;
   #print "$passes[$i]\n";
   #next if 1;
   `creduce --no-default-passes --add-pass $pass ./run_script.sh sample.c > log/runlog-$fileName.txt`;
   my $time = sprintf("%.3f", Time::HiRes::time() - $start);
   if(-e "sample.c.orig"){
      `mv sample.c reduced/sample-$fileName.c`;
      `mv sample.c.orig sample.c`;
   }
   print "$tool,$program,sample-$fileName.c,$fileName,$time\n";
}
