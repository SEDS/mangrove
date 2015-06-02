long long * CWE476_NULL_Pointer_Dereference__long_long_68_goodG2B_data;
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__long_long_68_goodG2B_data = data;
}
#endif
