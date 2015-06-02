#ifndef OMITGOOD
static void goodG2BSink(int * data)
{
}
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    goodG2BSink(data);
}
#endif
