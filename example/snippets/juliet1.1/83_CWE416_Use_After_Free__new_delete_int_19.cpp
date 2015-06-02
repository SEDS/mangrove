namespace CWE416_Use_After_Free__new_delete_int_19
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    data = new int;
    return;
}
#endif
}
