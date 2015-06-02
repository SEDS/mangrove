#ifndef OMITGOOD
void CWE843_Type_Confusion__short_53b_goodG2BSink(void * data);
static void goodG2B()
{
    void * data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    CWE843_Type_Confusion__short_53b_goodG2BSink(data);
}
#endif
