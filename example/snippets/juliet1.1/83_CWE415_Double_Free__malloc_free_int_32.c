#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    int * *data_ptr1 = &data;
    {
        free(data);
        *data_ptr1 = data;
    }
}
#endif
