long * CWE476_NULL_Pointer_Dereference__long_68_goodG2BData;
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__long_68_goodG2BData = data;
}
#endif
