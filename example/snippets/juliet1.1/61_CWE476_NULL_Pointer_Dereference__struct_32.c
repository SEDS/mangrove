#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    twoints * *data_ptr1 = &data;
    {
        {
            twoints tmp;
            data = &tmp;
        }
        *data_ptr1 = data;
    }
}
#endif
