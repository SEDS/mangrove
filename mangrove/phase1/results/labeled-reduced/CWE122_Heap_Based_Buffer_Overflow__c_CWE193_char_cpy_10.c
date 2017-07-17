 #include "std_testcase.h"
#define SRC_STRING "AAAAAAAAAA"
static void goodG2B2()
{
    char * data;
    data = NULL;
    if(globalTrue)
    {
        data = (char *)malloc((10+1)*sizeof(char));
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
        printLine(data);
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE193_char_cpy_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        strcpy(data, source);
*/

--fp-r--