typedef struct _CWE476_NULL_Pointer_Dereference__long_long_67_struct_type
{
    long long * a;
} CWE476_NULL_Pointer_Dereference__long_long_67_struct_type;
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    CWE476_NULL_Pointer_Dereference__long_long_67_struct_type my_struct;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    my_struct.a = data;
}
#endif
