#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_int_67_structType
{
    int * structFirst;
} CWE415_Double_Free__malloc_free_int_67_structType;
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_67_structType myStruct;
    free(data);
    myStruct.structFirst = data;
}
#endif
