#ifndef OMITGOOD
static void goodG2B()
{
    long * data;
    long * *dataPtr1 = &data;
    {
        {
            long tmpData = 5L;
            data = &tmpData;
        }
        *dataPtr1 = data;
    }
}
#endif
