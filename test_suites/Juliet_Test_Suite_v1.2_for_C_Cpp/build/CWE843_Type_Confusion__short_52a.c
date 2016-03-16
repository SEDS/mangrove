#include "std_testcase.h"
#ifndef OMITBAD
void CWE843_Type_Confusion__short_52b_badSink(void * data);
void CWE843_Type_Confusion__short_52_bad()
{
    void * data;
    data = NULL;
    {
        short shortBuffer = 8;
        data = &shortBuffer;
    }
    CWE843_Type_Confusion__short_52b_badSink(data);
}
#endif
#ifndef OMITGOOD
void CWE843_Type_Confusion__short_52b_goodG2BSink(void * data);
static void goodG2B()
{
    void * data;
    data = NULL;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    CWE843_Type_Confusion__short_52b_goodG2BSink(data);
}
void CWE843_Type_Confusion__short_52_good()
{
    goodG2B();
}
#endif
#ifdef INCLUDEMAIN
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE843_Type_Confusion__short_52_good();
    printLine("Finished good()");
#endif
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE843_Type_Confusion__short_52_bad();
    printLine("Finished bad()");
#endif
    return 0;
}
#endif
