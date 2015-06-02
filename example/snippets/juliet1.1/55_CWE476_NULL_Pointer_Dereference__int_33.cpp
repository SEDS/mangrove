namespace CWE476_NULL_Pointer_Dereference__int_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * &data_ref = data;
    {
        int tmp = 5;
        data = &tmp;
    }
    {
        int * data = data_ref;
    }
}
#endif
}
