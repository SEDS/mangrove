namespace CWE843_Type_Confusion__short_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * &data_ref = data;
    {
        int buf = 8;
        data = &buf;
    }
    {
        void * data = data_ref;
    }
}
#endif
}
