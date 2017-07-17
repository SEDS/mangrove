#include "std_testcase.h"
#define CHAR_ARRAY_SIZE (3 * sizeof(data) + 2)
void CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fgets_63b_goodG2BSink(int * dataPtr)
{
    int data = *dataPtr;
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