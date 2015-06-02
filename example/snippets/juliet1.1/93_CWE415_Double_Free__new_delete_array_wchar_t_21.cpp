namespace CWE415_Double_Free__new_delete_array_wchar_t_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(wchar_t * data)
{
    data = new wchar_t[100];
    delete [] data;
    goodB2G1_sink(data);
}
#endif
}
