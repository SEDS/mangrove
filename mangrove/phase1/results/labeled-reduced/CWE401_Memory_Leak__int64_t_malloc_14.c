#include "std_testcase.h"
static void goodB2G2()
{
    int64_t * data;
    data = NULL;
    if(globalFive==5)
    {
        data = (int64_t *)malloc(100*sizeof(int64_t));
        data[0] = 5LL;
        printLongLongLine(data[0]);
    }
    if(globalFive==5)
    {
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE401_Memory_Leak__int64_t_malloc_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------}
*/
--fp-r--