typedef struct _CWE843_Type_Confusion__char_67_structType
{
    void * structFirst;
} CWE843_Type_Confusion__char_67_structType;
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    CWE843_Type_Confusion__char_67_structType myStruct;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    myStruct.structFirst = data;
}
#endif
