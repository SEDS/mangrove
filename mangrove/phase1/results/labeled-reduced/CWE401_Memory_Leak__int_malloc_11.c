#include <wchar.h>
static void goodB2G2()
{
    int * data;
    data = NULL;
    if(globalReturnsTrue())
    {
        data = (int *)malloc(100*sizeof(int));
        data[0] = 5;
        printIntLine(data[0]);
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
    CWE401_Memory_Leak__int_malloc_11_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------}
*/
--fp-r--