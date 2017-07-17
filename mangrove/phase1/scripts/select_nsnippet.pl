#!/usr/bin/perl

use strict;
use 5.014;
use warnings;

my $n =$ARGV[0];

sub selectNSnippets($$){
   my $n =shift;
   my $grep_resultStr=shift;

   my $find="/home/ukoc/juliet/testcases";
   $find = quotemeta $find;
   my $replace="/Users/ugurmeryem/Juliet/r-testcases";
   $grep_resultStr =~ s/$find/$replace/g;

   my @snippetList=();
   my @grep_result = split("\n", $grep_resultStr);
   foreach (@grep_result) {
      my @lineArr=split("'",$_);
      push(@snippetList, $lineArr[1]);
   }
   
   my $len=scalar @snippetList;
   my %selectedLines = ();
   my $randLine = int(rand($len));
   while(keys %selectedLines < $n){
      $selectedLines{$randLine}=$snippetList[$randLine];
      $randLine = int(rand($len));
   }
   
   foreach (sort keys %selectedLines) {
      my $fileDir=$selectedLines{$_};
      `cp $fileDir labeled-reduced/`;
      $find="r-testcases";
      $find = quotemeta $find;
      $replace="testcases";
      $fileDir =~ s/$find/$replace/g;
      `cp $fileDir labeled-orig/`;
   }
}


selectNSnippets($n, `grep "reduced to:" /Users/ugurmeryem/juliet-logs/*`);