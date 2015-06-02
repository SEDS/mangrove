#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    long * dataArray[5];
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    dataArray[2] = data;
}
#endif
