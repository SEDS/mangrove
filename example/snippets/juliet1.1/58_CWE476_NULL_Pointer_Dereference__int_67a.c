typedef struct _CWE476_NULL_Pointer_Dereference__int_67_struct_type
{
    int * a;
} CWE476_NULL_Pointer_Dereference__int_67_struct_type;
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    CWE476_NULL_Pointer_Dereference__int_67_struct_type my_struct;
    {
        int tmp = 5;
        data = &tmp;
    }
    my_struct.a = data;
}
#endif
