#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * data_array[5];
    {
        int buf = 8;
        data = &buf;
    }
    data_array[2] = data;
}
#endif
