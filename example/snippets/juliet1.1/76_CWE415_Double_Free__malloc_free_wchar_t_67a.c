#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_wchar_t_67_struct_type
{
    wchar_t * a;
} CWE415_Double_Free__malloc_free_wchar_t_67_struct_type;
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    CWE415_Double_Free__malloc_free_wchar_t_67_struct_type my_struct;
    free(data);
    my_struct.a = data;
}
#endif
