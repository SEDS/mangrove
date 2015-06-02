namespace CWE476_NULL_Pointer_Dereference__long_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    long * &dataRef = data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    {
        long * data = dataRef;
    }
}
#endif
}
