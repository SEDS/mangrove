#include "std_testcase.h"
static void goodG2B2()
{
    int * data;
    data = NULL;
    if(GLOBAL_CONST_FIVE==5)
    {
        data = (int *)ALLOCA(10*sizeof(int));
    }
    {
        int source[10] = {0};
        memmove(data, source, 10*sizeof(int));
        printIntLine(data[0]);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE131_memmove_13_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Null pointer passed as an argument to a 'nonnull' parameter------        memmove(data, source, 10*sizeof(int));
*/

--fp-r--