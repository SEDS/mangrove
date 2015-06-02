#include "std_testcase.h"
typedef union
{
    int * unionFirst;
} CWE415_Double_Free__malloc_free_int_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
