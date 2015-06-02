typedef struct _CWE843_Type_Confusion__char_67_struct_type
{
    void * a;
} CWE843_Type_Confusion__char_67_struct_type;
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    CWE843_Type_Confusion__char_67_struct_type my_struct;
    {
        int buf = 8;
        data = &buf;
    }
    my_struct.a = data;
}
#endif
