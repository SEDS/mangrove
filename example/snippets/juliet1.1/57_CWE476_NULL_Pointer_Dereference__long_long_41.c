#ifndef OMITGOOD
static void goodG2B_sink(long long * data)
{
}
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    goodG2B_sink(data);
}
#endif
