namespace CWE415_Double_Free__new_delete_array_int_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(int * data)
{
    data = new int[100];
    delete [] data;
    goodB2G1_sink(data);
}
#endif
}
