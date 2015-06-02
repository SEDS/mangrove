#include "std_testcase.h"
typedef union
{
    long * unionFirst;
} CWE415_Double_Free__malloc_free_long_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    long * data;
    CWE415_Double_Free__malloc_free_long_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
