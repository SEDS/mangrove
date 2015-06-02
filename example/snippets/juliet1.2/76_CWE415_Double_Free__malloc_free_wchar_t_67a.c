#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_wchar_t_67_structType
{
    wchar_t * structFirst;
} CWE415_Double_Free__malloc_free_wchar_t_67_structType;
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    CWE415_Double_Free__malloc_free_wchar_t_67_structType myStruct;
    free(data);
    myStruct.structFirst = data;
}
#endif
