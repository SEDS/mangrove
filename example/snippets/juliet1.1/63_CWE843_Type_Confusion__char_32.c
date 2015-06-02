#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    void * *data_ptr1 = &data;
    {
        {
            int buf = 8;
            data = &buf;
        }
        *data_ptr1 = data;
    }
}
#endif
