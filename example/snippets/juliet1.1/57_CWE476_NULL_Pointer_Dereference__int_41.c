#ifndef OMITGOOD
static void goodG2B_sink(int * data)
{
}
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    goodG2B_sink(data);
}
#endif
