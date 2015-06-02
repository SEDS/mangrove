namespace CWE416_Use_After_Free__new_delete_wchar_t_19
{
#ifndef OMITGOOD
static void goodG2B()
{
    wchar_t * data;
    data = new wchar_t;
    return;
}
#endif
}
