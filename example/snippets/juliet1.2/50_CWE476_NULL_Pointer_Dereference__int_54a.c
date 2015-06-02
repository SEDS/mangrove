#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__int_54b_goodG2BSink(int * data);
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int_54b_goodG2BSink(data);
}
#endif
