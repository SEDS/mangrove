namespace CWE415_Double_Free__new_delete_long_long_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(long long * data)
{
    data = new long long;
    delete data;
    goodB2G2_sink(data);
}
#endif
}
