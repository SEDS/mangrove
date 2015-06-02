#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * data_array[5];
    {
        int tmp = 5;
        data = &tmp;
    }
    data_array[2] = data;
}
#endif
