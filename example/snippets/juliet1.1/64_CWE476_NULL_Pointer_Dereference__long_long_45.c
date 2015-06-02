static long long * CWE476_NULL_Pointer_Dereference__long_long_45_goodG2B_data;
#ifndef OMITGOOD
static void goodG2B_sink()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__long_long_45_goodG2B_data = data;
}
#endif
