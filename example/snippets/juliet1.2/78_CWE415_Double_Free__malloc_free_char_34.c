#include "std_testcase.h"
typedef union
{
    char * unionFirst;
} CWE415_Double_Free__malloc_free_char_34_unionType;
#ifndef OMITBAD
static void goodB2G()
{
    char * data;
    CWE415_Double_Free__malloc_free_char_34_unionType myUnion;
    free(data);
    myUnion.unionFirst = data;
}
#endif
