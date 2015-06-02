#include "std_testcase.h"
typedef struct _CWE415_Double_Free__malloc_free_int64_t_67_structType
{
    int64_t * structFirst;
} CWE415_Double_Free__malloc_free_int64_t_67_structType;
#ifndef OMITBAD
static void goodB2G()
{
    int64_t * data;
    CWE415_Double_Free__malloc_free_int64_t_67_structType myStruct;
    free(data);
    myStruct.structFirst = data;
}
#endif
