namespace CWE762_Mismatched_Memory_Management_Routines__new_delete_array_long_long_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(long long * data)
{
    {
        delete [] data;
    }
    data = new long long;
    goodB2G1_sink(data);
}
#endif
}
