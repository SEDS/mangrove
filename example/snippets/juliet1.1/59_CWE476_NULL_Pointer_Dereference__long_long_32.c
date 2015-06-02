#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    long long * *data_ptr1 = &data;
    {
        {
            long long tmp = 5L;
            data = &tmp;
        }
        *data_ptr1 = data;
    }
}
#endif
