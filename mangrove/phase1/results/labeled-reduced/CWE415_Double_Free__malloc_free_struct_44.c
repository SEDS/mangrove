#include "std_testcase.h"
static void goodB2GSink(twoIntsStruct * data)
{
    ; 
}
static void goodB2G()
{
    twoIntsStruct * data;
    void (*funcPtr) (twoIntsStruct *) = goodB2GSink;
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    free(data);
    funcPtr(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE415_Double_Free__malloc_free_struct_44_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Use of memory after it is freed------    funcPtr(data);
*/

--fp-r--