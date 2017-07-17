#include "std_testcase.h"
typedef union
{
    int * unionFirst;
    int * unionSecond;
} CWE122_Heap_Based_Buffer_Overflow__CWE131_memcpy_34_unionType;
static void goodG2B()
{
    int * data;
    CWE122_Heap_Based_Buffer_Overflow__CWE131_memcpy_34_unionType myUnion;
    data = NULL;
    data = (int *)malloc(10*sizeof(int));
    myUnion.unionFirst = data;
    {
        int * data = myUnion.unionSecond;
        {
            int source[10] = {0};
            memcpy(data, source, 10*sizeof(int));
            printIntLine(data[0]);
            free(data);
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__CWE131_memcpy_34_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'myUnion.unionFirst'------        int * data = myUnion.unionSecond;
*/

--tp-r--