typedef union
{
    int * a;
} CWE476_NULL_Pointer_Dereference__int_34_union_type;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    CWE476_NULL_Pointer_Dereference__int_34_union_type my_union;
    {
        int tmp = 5;
        data = &tmp;
    }
    my_union.a = data;
}
#endif
