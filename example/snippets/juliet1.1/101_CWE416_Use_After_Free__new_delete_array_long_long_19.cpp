namespace CWE416_Use_After_Free__new_delete_array_long_long_19
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    data = new long long[100];
    return;
}
#endif
}
