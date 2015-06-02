#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    long long * data_array[5];
    {
        long long tmp = 5L;
        data = &tmp;
    }
    data_array[2] = data;
}
#endif
