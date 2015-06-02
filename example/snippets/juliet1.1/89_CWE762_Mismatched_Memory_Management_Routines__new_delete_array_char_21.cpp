namespace CWE762_Mismatched_Memory_Management_Routines__new_delete_array_char_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(char * data)
{
    {
        delete [] data;
    }
    data = new char;
    goodB2G1_sink(data);
}
#endif
}
