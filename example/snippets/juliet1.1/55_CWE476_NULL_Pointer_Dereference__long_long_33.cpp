namespace CWE476_NULL_Pointer_Dereference__long_long_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    long long * &data_ref = data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    {
        long long * data = data_ref;
    }
}
#endif
}
