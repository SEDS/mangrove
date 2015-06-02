#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_long_long_67_struct_type
{
    long long * a;
} CWE415_Double_Free__malloc_free_long_long_67_struct_type;
#ifndef OMITBAD
static void goodB2G()
{
    long long * data;
    CWE415_Double_Free__malloc_free_long_long_67_struct_type my_struct;
    free(data);
    my_struct.a = data;
}
#endif
