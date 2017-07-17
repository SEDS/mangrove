#include <stdio.h>

void f_helper(int *s){
   for (int i = 0; i < 256; i++)  (*s)++;
}

int main() {
   int yy[256];
   int tmp = 0;
   int *p_tmp = &tmp;
   
   f_helper(p_tmp);
   for (int i = 0; i <= *p_tmp; i++)   yy[i] = i;

   /* The false warning:
    smple-useofgarbageval.c:20:13: warning: The left operand of '==' is a garbage value
               if (yy[1]==1) {
    */
   
   if (yy[1]==1) {
      printf("hi\n");
   }

   return 0;
}