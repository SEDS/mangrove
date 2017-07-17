#include "std_testcase.h"
static void goodB2G1()
{
    struct _twoIntsStruct * data;
    data = NULL;
    if(globalFive==5)
    {
        data = (struct _twoIntsStruct *)malloc(100*sizeof(struct _twoIntsStruct));
        data[0].intOne = 0;
        data[0].intTwo = 0;
        printStructLine((twoIntsStruct *)&data[0]);
    }
    if(globalFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE401_Memory_Leak__struct_twoIntsStruct_malloc_14_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printLine("Benign, fixed string");
*/
--fp-r--