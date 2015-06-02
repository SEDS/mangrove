typedef union
{
    int * unionFirst;
} CWE476_NULL_Pointer_Dereference__int_34_unionType;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    CWE476_NULL_Pointer_Dereference__int_34_unionType myUnion;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    myUnion.unionFirst = data;
}
#endif
