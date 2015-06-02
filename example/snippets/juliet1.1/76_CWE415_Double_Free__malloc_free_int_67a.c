#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_int_67_struct_type
{
    int * a;
} CWE415_Double_Free__malloc_free_int_67_struct_type;
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_67_struct_type my_struct;
    free(data);
    my_struct.a = data;
}
#endif
