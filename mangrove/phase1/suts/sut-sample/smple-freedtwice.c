#include <stdlib.h>
#include <stdio.h>


int somenumber() {
   int z=rand();
   return z;
}

int somenumber2() {
   int z=rand();
   return z;
}

int main(int argc, char** argv) {
   int * p = (int *)malloc(10 * sizeof(int));
   int z;
   z=somenumber();
   int y=3;
   if ((z % 10) >= 11){ free(p); }
   free(p);
   printf("Done, %d !\n", y);
   return 0;
}