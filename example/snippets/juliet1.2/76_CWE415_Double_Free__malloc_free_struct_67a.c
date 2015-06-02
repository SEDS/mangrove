#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_struct_67_structType
{
    twoIntsStruct * structFirst;
} CWE415_Double_Free__malloc_free_struct_67_structType;
#ifndef OMITBAD
static void goodB2G()
{
    twoIntsStruct * data;
    CWE415_Double_Free__malloc_free_struct_67_structType myStruct;
    free(data);
    myStruct.structFirst = data;
}
#endif
