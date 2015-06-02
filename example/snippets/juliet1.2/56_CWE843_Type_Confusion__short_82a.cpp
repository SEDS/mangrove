#include "CWE843_Type_Confusion__short_82.h"
namespace CWE843_Type_Confusion__short_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    CWE843_Type_Confusion__short_82_base* baseObject = new CWE843_Type_Confusion__short_82_goodG2B;
    baseObject->action(data);
}
#endif
}
