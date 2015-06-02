#include "std_testcase.h"
typedef union
{
    int * a;
} CWE415_Double_Free__malloc_free_int_34_union_type;
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_34_union_type my_union;
    free(data);
    my_union.a = data;
}
#endif
