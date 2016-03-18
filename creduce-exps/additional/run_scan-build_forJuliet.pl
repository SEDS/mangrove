#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;

my $workDir ="/home/ukoc/juliet/testcases"; #$ARGV[0];
my $logDir="/home/ukoc/juliet-logs/";
my @CWEFolders = ();

sub run_sb($$){
    my $runDir=shift;
    my $logFile=shift;
    `echo "Runing under $runDir" > $logFile`;
    `cd $runDir && scan-build make CFLAGS="-c -D OMITBAD" >> $logFile 2>&1`;
    `./run_creduce_forJuliet.pl $runDir $logFile`;
    `cd $runDir && rm -fr *.o *.orig`;
}

opendir(DIR, $workDir) or die $!;
while (my $folder = readdir(DIR)) {
   if($folder eq ".." or $folder eq "."){ next; }
   push(@CWEFolders, $folder);
}

foreach my $folder (@CWEFolders){
   my $logfile=$logDir.substr($folder, 0, 6)."-scanbuild.log";
   if (-d "$workDir/$folder/s01") {
      opendir(DIR, "$workDir/$folder") or die $!;
      while (my $subfolder = readdir(DIR)) {
         if($subfolder eq ".." or $subfolder eq "." or (not (-e "$workDir/$folder/$subfolder/Makefile"))){ next; }
         $logfile=$logDir.substr($folder, 0, 6).$subfolder."-scanbuild.log";
	 run_sb("$workDir/$folder/$subfolder", $logfile);
      }
   } elsif (-e "$workDir/$folder/Makefile"){
       run_sb("$workDir/$folder", $logfile);
   }
}
