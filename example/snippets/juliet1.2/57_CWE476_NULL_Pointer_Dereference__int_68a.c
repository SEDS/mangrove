int * CWE476_NULL_Pointer_Dereference__int_68_goodG2BData;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int_68_goodG2BData = data;
}
#endif
