#include "std_testcase.h"
static void goodB2G()
{
    twoIntsStruct * data;
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    free(data);
    CWE415_Double_Free__malloc_free_struct_53b_goodB2GSink(data);
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE415_Double_Free__malloc_free_struct_53_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Use of memory after it is freed------    CWE415_Double_Free__malloc_free_struct_53b_goodB2GSink(data);
*/

--up-r--