#include "std_testcase.h"
typedef union
{
    wchar_t * unionFirst;
} CWE415_Double_Free__malloc_free_wchar_t_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    CWE415_Double_Free__malloc_free_wchar_t_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
