#include "std_testcase.h"
static void goodG2B1()
{
    int64_t * data;
    data = NULL;
    if(globalFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = (int64_t *)malloc(100*sizeof(int64_t));
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5LL;
            }
        }
    }
    if(globalFive==5)
    {
        printLongLongLine(data[0]);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE416_Use_After_Free__malloc_free_int64_t_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Array access (from variable 'data') results in a null pointer dereference------        printLongLongLine(data[0]);
*/
--fp-r--