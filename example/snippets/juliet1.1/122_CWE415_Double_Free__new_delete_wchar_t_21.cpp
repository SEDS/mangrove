namespace CWE415_Double_Free__new_delete_wchar_t_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(wchar_t * data)
{
    data = new wchar_t;
    delete data;
    goodB2G2_sink(data);
}
#endif
}
