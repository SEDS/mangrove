#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__int_54b_goodG2B_sink(int * data);
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    CWE476_NULL_Pointer_Dereference__int_54b_goodG2B_sink(data);
}
#endif
