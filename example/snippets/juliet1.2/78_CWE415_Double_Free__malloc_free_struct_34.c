#include "std_testcase.h"
typedef union
{
    twoIntsStruct * unionFirst;
} CWE415_Double_Free__malloc_free_struct_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    twoIntsStruct * data;
    CWE415_Double_Free__malloc_free_struct_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
