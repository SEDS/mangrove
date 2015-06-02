namespace CWE843_Type_Confusion__short_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * &dataRef = data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    {
        void * data = dataRef;
    }
}
#endif
}
