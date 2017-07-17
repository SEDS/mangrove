#include <stdlib.h>
#include <stdio.h>

int x, y;

int foo(int z){
   printf("%d",x);
   if (z){ x=0;
  	}else{ x=1; }

   if (z){ y=100/z;
  	}else{ y=100/x; }

   return y;
}

int main(int argc, char** argv) {
   int z=atoi(argv[1]);
   foo(z);
   printf("%d", y);
}