typedef struct _CWE476_NULL_Pointer_Dereference__int_67_structType
{
    int * structFirst;
} CWE476_NULL_Pointer_Dereference__int_67_structType;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    CWE476_NULL_Pointer_Dereference__int_67_structType myStruct;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    myStruct.structFirst = data;
}
#endif
