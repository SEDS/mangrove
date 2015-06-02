#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_long_67_structType
{
    long * structFirst;
} CWE415_Double_Free__malloc_free_long_67_structType;
#ifndef OMITBAD
static void goodB2G()
{
    long * data;
    CWE415_Double_Free__malloc_free_long_67_structType myStruct;
    free(data);
    myStruct.structFirst = data;
}
#endif
