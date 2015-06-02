static int * CWE476_NULL_Pointer_Dereference__int_45_goodG2BData;
#ifndef OMITGOOD
static void goodG2BSink()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int_45_goodG2BData = data;
}
#endif
