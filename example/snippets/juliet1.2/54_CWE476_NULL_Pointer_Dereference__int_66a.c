#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * dataArray[5];
    {
        int tmpData = 5;
        data = &tmpData;
    }
    dataArray[2] = data;
}
#endif
