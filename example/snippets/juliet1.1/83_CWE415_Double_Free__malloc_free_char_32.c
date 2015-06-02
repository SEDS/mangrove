#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    char * data;
    char * *data_ptr1 = &data;
    {
        free(data);
        *data_ptr1 = data;
    }
}
#endif
