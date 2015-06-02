int * CWE476_NULL_Pointer_Dereference__int_68_goodG2B_data;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__int_68_goodG2B_data = data;
}
#endif
