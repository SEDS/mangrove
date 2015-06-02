#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__long_long_51b_goodG2B_sink(long long * data);
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__long_long_51b_goodG2B_sink(data);
}
#endif
