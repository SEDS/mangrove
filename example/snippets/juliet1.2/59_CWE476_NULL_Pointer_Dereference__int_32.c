#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * *dataPtr1 = &data;
    {
        {
            int tmpData = 5;
            data = &tmpData;
        }
        *dataPtr1 = data;
    }
}
#endif
