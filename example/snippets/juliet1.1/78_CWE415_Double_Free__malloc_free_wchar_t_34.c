#include "std_testcase.h"
typedef union
{
    wchar_t * a;
} CWE415_Double_Free__malloc_free_wchar_t_34_union_type;
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    CWE415_Double_Free__malloc_free_wchar_t_34_union_type my_union;
    free(data);
    my_union.a = data;
}
#endif
