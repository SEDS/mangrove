#include "CWE843_Type_Confusion__short_81.h"
namespace CWE843_Type_Confusion__short_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    const CWE843_Type_Confusion__short_81_base& o = CWE843_Type_Confusion__short_81_goodG2B();
    o.action(data);
}
#endif
}
