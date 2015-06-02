#include "std_testcase.h"
#ifndef _WIN32
static void good2()
{
    {
    {
        struct _twoints * data = (struct _twoints *)malloc(100*sizeof(struct _twoints));
        data = (struct _twoints *)realloc(data, (130000)*sizeof(struct _twoints));
    }
    }
}
#endif
