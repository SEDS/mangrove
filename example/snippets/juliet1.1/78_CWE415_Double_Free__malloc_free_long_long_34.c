#include "std_testcase.h"
typedef union
{
    long long * a;
} CWE415_Double_Free__malloc_free_long_long_34_union_type;
#ifndef OMITBAD
static void goodB2G()
{
    long long * data;
    CWE415_Double_Free__malloc_free_long_long_34_union_type my_union;
    free(data);
    my_union.a = data;
}
#endif
