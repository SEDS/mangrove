typedef union
{
    void * a;
} CWE843_Type_Confusion__char_34_union_type;
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    CWE843_Type_Confusion__char_34_union_type my_union;
    {
        int buf = 8;
        data = &buf;
    }
    my_union.a = data;
}
#endif
