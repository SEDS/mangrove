 #include "std_testcase.h"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(globalFive==5)
    {
        data = (char *)malloc(100*sizeof(char));
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        memmove(data, source, 100*sizeof(char));
        data[100-1] = '\0'; 
        printLine(data);
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_memmove_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memmove(data, source, 100*sizeof(char));
*/
--fp-r--