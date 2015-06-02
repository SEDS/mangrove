typedef union
{
    long * unionFirst;
} CWE476_NULL_Pointer_Dereference__long_34_unionType;
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    CWE476_NULL_Pointer_Dereference__long_34_unionType myUnion;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    myUnion.unionFirst = data;
}
#endif
