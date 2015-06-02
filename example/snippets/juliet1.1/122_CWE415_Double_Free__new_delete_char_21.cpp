namespace CWE415_Double_Free__new_delete_char_21
{
#ifndef OMITGOOD
static void goodB2G2_sink(char * data)
{
    data = new char;
    delete data;
    goodB2G2_sink(data);
}
#endif
}
