namespace CWE415_Double_Free__new_delete_int_21
{
#ifndef OMITGOOD
static void goodB2G1_sink(int * data)
{
    data = new int;
    delete data;
    goodB2G1_sink(data);
}
#endif
}
