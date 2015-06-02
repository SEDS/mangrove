#include "std_testcase.h"
typedef union
{
    char * a;
} CWE415_Double_Free__malloc_free_char_34_union_type;
#ifndef OMITBAD
static void goodB2G()
{
    char * data;
    CWE415_Double_Free__malloc_free_char_34_union_type my_union;
    free(data);
    my_union.a = data;
}
#endif
