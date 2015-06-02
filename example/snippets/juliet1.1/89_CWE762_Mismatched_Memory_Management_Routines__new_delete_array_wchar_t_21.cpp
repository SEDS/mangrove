namespace CWE762_Mismatched_Memory_Management_Routines__new_delete_array_wchar_t_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(wchar_t * data)
{
    {
        delete [] data;
    }
    data = new wchar_t;
    goodB2G1_sink(data);
}
#endif
}
