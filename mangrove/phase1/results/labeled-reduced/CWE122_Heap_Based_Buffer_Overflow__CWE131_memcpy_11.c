 #include "std_testcase.h"
static void goodG2B2()
{
    int * data;
    data = NULL;
    if(globalReturnsTrue())
    {
        data = (int *)malloc(10*sizeof(int));
    }
    {
        int source[10] = {0};
        memcpy(data, source, 10*sizeof(int));
        printIntLine(data[0]);
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__CWE131_memcpy_11_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memcpy(data, source, 10*sizeof(int));
*/

--fp-r--