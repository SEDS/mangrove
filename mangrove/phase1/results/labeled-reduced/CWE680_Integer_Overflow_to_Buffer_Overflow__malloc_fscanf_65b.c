#include "std_testcase.h"
void CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_65b_goodG2BSink(int data)
{
    {
        size_t i;
        int *intPointer;
        intPointer = (int*)malloc(data * sizeof(int));
        for (i = 0; i < (size_t)data; i++)
        {
            intPointer[i] = 0; 
        }
        printIntLine(intPointer[0]);
        free(intPointer);
    }
}
/* Warning description
Function call argument is an uninitialized value------        printIntLine(intPointer[0]);
*/
--tp-r--