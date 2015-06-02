#include "CWE843_Type_Confusion__char_81.h"
namespace CWE843_Type_Confusion__char_81
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    const CWE843_Type_Confusion__char_81_base& baseObject = CWE843_Type_Confusion__char_81_goodG2B();
    baseObject.action(data);
}
#endif
}
