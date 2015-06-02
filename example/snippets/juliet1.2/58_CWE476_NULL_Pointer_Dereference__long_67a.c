typedef struct _CWE476_NULL_Pointer_Dereference__long_67_structType
{
    long * structFirst;
} CWE476_NULL_Pointer_Dereference__long_67_structType;
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    CWE476_NULL_Pointer_Dereference__long_67_structType myStruct;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    myStruct.structFirst = data;
}
#endif
