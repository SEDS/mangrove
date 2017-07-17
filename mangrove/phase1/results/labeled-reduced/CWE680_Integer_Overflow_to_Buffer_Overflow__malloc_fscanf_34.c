#include "std_testcase.h"
typedef union
{
    int unionFirst;
    int unionSecond;
} CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_unionType;
static void goodG2B()
{
    int data;
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_unionType myUnion;
    data = -1;
    data = 20;
    myUnion.unionFirst = data;
    {
        int data = myUnion.unionSecond;
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
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_fscanf_34_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Function call argument is an uninitialized value------            printIntLine(intPointer[0]);
*/
--tp-r--