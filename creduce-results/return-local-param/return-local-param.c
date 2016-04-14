#include "std_testcase.h"
static int goodG2B2Static = 0;
static char * goodG2B2Source(char * data)
{
    return data;
}
static void goodG2B2()
{
    char * data;
    char dataBuffer[100];
    data = dataBuffer;
    data = goodG2B2Source(data);
}
void CWE665_Improper_Initialization__char_cat_21_good()
{
    goodG2B2();
}
int main(int argc, char * argv[])
{
    CWE665_Improper_Initialization__char_cat_21_good();
    return 0;
}