#ifndef OMITGOOD
void CWE843_Type_Confusion__short_53b_goodG2B_sink(void * data);
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    CWE843_Type_Confusion__short_53b_goodG2B_sink(data);
}
#endif
