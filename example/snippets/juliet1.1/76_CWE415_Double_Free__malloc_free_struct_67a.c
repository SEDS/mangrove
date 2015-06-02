#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_struct_67_struct_type
{
    twoints * a;
} CWE415_Double_Free__malloc_free_struct_67_struct_type;
#ifndef OMITBAD
static void goodB2G()
{
    twoints * data;
    CWE415_Double_Free__malloc_free_struct_67_struct_type my_struct;
    free(data);
    my_struct.a = data;
}
#endif
