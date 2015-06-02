namespace CWE415_Double_Free__new_delete_array_long_long_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(long long * data)
{
    data = new long long[100];
    delete [] data;
    goodB2G1_sink(data);
}
#endif
}
