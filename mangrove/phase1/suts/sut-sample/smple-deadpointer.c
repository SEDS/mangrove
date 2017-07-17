#include <stdio.h>

int main()
{
   int * data;
   if (1){
      int tmpData = 5;
      data = &tmpData;
   }
   printf("%d",*data);
   return 0;
}
