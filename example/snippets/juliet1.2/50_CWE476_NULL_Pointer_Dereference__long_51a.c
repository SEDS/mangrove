#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__long_51b_goodG2BSink(long * data);
static void goodG2B()
{
    long * data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__long_51b_goodG2BSink(data);
}
#endif
