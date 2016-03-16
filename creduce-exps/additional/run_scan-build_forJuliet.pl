#!/usr/bin/perl

use strict;
use 5.014;
use warnings;
use Time::HiRes;

my $workDir ="/home/ukoc/juliet/testcases"; #$ARGV[0];
my $logDir="/home/ukoc/juliet-logs/";
my @CWEFolders = ();

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
         if($subfolder eq ".." or $subfolder eq "."){ next; }
         if (-e "$workDir/$folder/$subfolder/Makefile"){
            $logfile=$logDir.substr($folder, 0, 6).$subfolder."-scanbuild.log";
	    `echo "Runing under $folder" > $logfile`;
            `cd $workDir/$folder/$subfolder && scan-build gcc -c -I ~/juliet/testcasesupport -D OMITBAD *.cpp >> $logfile 2>&1`;
            `cd $workDir/$folder/$subfolder && scan-build gcc -c -I ~/juliet/testcasesupport -D OMITBAD *.c >> $logfile 2>&1`;

            `./run_creduce_forJuliet.pl $workDir/$folder/$subfolder $logfile`;
            `cd $workDir/$folder/$subfolder && rm -fr *.o *.orig`;
         }
      }
   } elsif (-e "$workDir/$folder/Makefile"){
      `echo "Runing under $folder" > $logfile`;
      `cd $workDir/$folder && scan-build gcc -c -I ~/juliet/testcasesupport -D OMITBAD *.cpp >> $logfile 2>&1`;
      `cd $workDir/$folder && scan-build gcc -c -I ~/juliet/testcasesupport -D OMITBAD *.c >> $logfile 2>&1`;
      `./run_creduce_forJuliet.pl $workDir/$folder $logfile`;
      `cd $workDir/$folder && rm -fr *.o *.orig`;
   }
}
