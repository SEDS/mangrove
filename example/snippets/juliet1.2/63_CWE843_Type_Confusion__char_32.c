#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * *dataPtr1 = &data;
    {
        {
            int intBuffer = 8;
            data = &intBuffer;
        }
        *dataPtr1 = data;
    }
}
#endif
