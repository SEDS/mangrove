#include "CWE843_Type_Confusion__char_82.h"
namespace CWE843_Type_Confusion__char_82
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    CWE843_Type_Confusion__char_82_base* o = new CWE843_Type_Confusion__char_82_goodG2B;
    o->action(data);
}
#endif
}
