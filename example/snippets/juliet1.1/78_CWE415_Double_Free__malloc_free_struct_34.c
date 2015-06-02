#include "std_testcase.h"
typedef union
{
    twoints * a;
} CWE415_Double_Free__malloc_free_struct_34_union_type;
#ifndef OMITBAD
static void goodB2G()
{
    twoints * data;
    CWE415_Double_Free__malloc_free_struct_34_union_type my_union;
    free(data);
    my_union.a = data;
}
#endif
