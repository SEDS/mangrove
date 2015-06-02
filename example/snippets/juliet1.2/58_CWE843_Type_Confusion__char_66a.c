#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * dataArray[5];
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    dataArray[2] = data;
}
#endif
