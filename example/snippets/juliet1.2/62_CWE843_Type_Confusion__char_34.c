typedef union
{
    void * unionFirst;
} CWE843_Type_Confusion__char_34_unionType;
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    CWE843_Type_Confusion__char_34_unionType myUnion;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    myUnion.unionFirst = data;
}
#endif
