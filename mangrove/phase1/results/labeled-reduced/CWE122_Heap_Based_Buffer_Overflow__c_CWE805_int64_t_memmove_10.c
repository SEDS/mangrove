 #include "std_testcase.h"
static void goodG2B2()
{
    int64_t * data;
    data = NULL;
    if(globalTrue)
    {
        data = (int64_t *)malloc(100*sizeof(int64_t));
    }
    {
        int64_t source[100] = {0}; 
        memmove(data, source, 100*sizeof(int64_t));
        printLongLongLine(data[0]);
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_int64_t_memmove_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memmove(data, source, 100*sizeof(int64_t));
*/

--fp-r--