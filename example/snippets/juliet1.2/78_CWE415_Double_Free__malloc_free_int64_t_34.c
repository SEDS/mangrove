#include "std_testcase.h"
typedef union
{
    int64_t * unionFirst;
} CWE415_Double_Free__malloc_free_int64_t_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    int64_t * data;
    CWE415_Double_Free__malloc_free_int64_t_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
