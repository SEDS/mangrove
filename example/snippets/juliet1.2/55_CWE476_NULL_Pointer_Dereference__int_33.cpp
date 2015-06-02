namespace CWE476_NULL_Pointer_Dereference__int_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * &dataRef = data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    {
        int * data = dataRef;
    }
}
#endif
}
