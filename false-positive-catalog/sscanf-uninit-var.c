// Juliet testcasesupport/io.c
// Structure: sscanf-uninit-var.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   int myInt;
   char dtm[10];
   
   strcpy(dtm, "7");
   sscanf(dtm, "%d", &myInt);

   // CodeSonar FP: Uninitialized Variable. myInt was not initialized.
   // scan-build FP: none
   // Cppcheck FP: none
   printf("%d\n", myInt);
    
   return(0);
}