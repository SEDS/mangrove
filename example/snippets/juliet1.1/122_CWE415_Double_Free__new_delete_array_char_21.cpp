namespace CWE415_Double_Free__new_delete_array_char_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(char * data)
{
    data = new char[100];
    delete [] data;
    goodB2G2_sink(data);
}
#endif
}
