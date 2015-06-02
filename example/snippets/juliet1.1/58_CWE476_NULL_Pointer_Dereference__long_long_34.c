typedef union
{
    long long * a;
} CWE476_NULL_Pointer_Dereference__long_long_34_union_type;
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    CWE476_NULL_Pointer_Dereference__long_long_34_union_type my_union;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    my_union.a = data;
}
#endif
