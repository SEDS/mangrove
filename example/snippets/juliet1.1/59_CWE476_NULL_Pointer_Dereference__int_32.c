#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    int * *data_ptr1 = &data;
    {
        {
            int tmp = 5;
            data = &tmp;
        }
        *data_ptr1 = data;
    }
}
#endif
