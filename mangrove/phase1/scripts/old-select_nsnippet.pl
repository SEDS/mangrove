#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;

my $n =$ARGV[0];

sub selectNSnippets($$){
   my $n =shift;
   my $cmd =shift;
   
   my @snippetList=();
   my $grep_resultStr=$cmd;
   my $find="/home/ukoc/juliet/testcases";
   $find = quotemeta $find;
   my $replace="/Users/ugurmeryem/Juliet/r-testcases";
   $grep_resultStr =~ s/$find/$replace/g;
   #print $grep_resultStr;
   my @grep_result = split("\n", $grep_resultStr);
   foreach (@grep_result) {
      my @lineArr=split("'",$_);
      push(@snippetList, $lineArr[1]);
   }
   
   my $len=scalar @snippetList;
   
   my %selectedLines = ();
   my %selectedWarnings = ();
   while(keys %selectedLines < $n){
      my $randLine = int(rand($len));
      #selecting files only with one warning
      my @tmp_arr=split("/",$snippetList[$randLine]);
      my $tmp_arr_len=scalar @tmp_arr;
      my $fileName=$tmp_arr[$tmp_arr_len-1];
      my $result=`grep "$fileName:" /Users/ugurmeryem/juliet-logs/*-creduce.log`;
      my @resultArr=split("\n",$result);
      
      if( 1 == scalar @resultArr){
         $selectedLines{$randLine}=$snippetList[$randLine];
         my @desc=split("[c|cpp]:",$resultArr[0]);
         $selectedWarnings{$randLine}=$desc[1];
      }
   }
   foreach (sort keys %selectedLines) {
      my $fileDir=$selectedLines{$_};
      `cp $fileDir labeled-reduced/`;
      $find="r-testcases";
      $find = quotemeta $find;
      $replace="testcases";
      $fileDir =~ s/$find/$replace/g;
      `cp $fileDir labeled-orig/`;
      my @tmp_arr=split("/",$fileDir);
      my $tmp_arr_len=scalar @tmp_arr;
      my $fileName=$tmp_arr[$tmp_arr_len-1];
      `cd labeled-reduced && echo "$selectedWarnings{$_}" >> $fileName 2>&1`;
      `open -a TextWrangler labeled-reduced/*`;
      `open -a TextWrangler labeled-orig/*`;
   }
   return %selectedLines;
}


selectNSnippets($n, `grep "reduced to:" /Users/ugurmeryem/juliet-logs/*`);