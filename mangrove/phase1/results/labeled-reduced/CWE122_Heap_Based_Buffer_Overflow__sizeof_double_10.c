 #include "std_testcase.h"
static void goodG2B2()
{
    double * data;
    data = NULL;
    if(globalTrue)
    {
        data = (double *)malloc(sizeof(*data));
        *data = 1.7E300;
    }
    printDoubleLine(*data);
    free(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__sizeof_double_10_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Dereference of null pointer (loaded from variable 'data')------    printDoubleLine(*data);
*/

--fp-r--