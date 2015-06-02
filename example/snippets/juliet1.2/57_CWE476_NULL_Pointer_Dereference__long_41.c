#ifndef OMITGOOD
static void goodG2BSink(long * data)
{
}
static void goodG2B()
{
    long * data;
    {
        long tmpData = 5L;
        data = &tmpData;
    }
    goodG2BSink(data);
}
#endif
