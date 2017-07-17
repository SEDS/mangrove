#include <stdlib.h>
#include <stdio.h>

#define LB 256

struct mystruct{
   int lb;
};

void makeMaps_e(struct mystruct *s){
   s->lb = 0;
   for (int i = 0; i < LB; i++)
     // if (1) {
         s->lb++;
      //}
}

int main() {
   int yy[LB], ll_i = 1, i=0;
   struct mystruct tmp;
   struct mystruct *p_tmp=&tmp;
   
   makeMaps_e(p_tmp);
   printf("%d\n",p_tmp->lb);
   for (i = 0; i <= p_tmp->lb; i++)   yy[i] = i;
   
   if (yy[1]==ll_i) {
      printf("hi\n");
   }

   return 0;
}