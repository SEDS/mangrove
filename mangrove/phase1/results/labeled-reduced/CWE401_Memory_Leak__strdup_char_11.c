#include "std_testcase.h"
static void goodB2G2()
{
    char * data;
    data = NULL;
    if(globalReturnsTrue())
    {
        {
            char myString[] = "myString";
            data = strdup(myString);
            printLine(data);
        }
    }
    if(globalReturnsTrue())
    {
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE401_Memory_Leak__strdup_char_11_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------}
*/
--fp-r--