namespace CWE416_Use_After_Free__new_delete_char_19
{
#ifndef OMITGOOD
static void goodG2B()
{
    char * data;
    data = new char;
    return;
}
#endif
}
