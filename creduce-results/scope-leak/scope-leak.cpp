#include "std_testcase.h"
static void goodG2B()
{
    char * data;
    char * *dataPtr1 = &data;
    char * *dataPtr2 = &data;
    data = new char[100];
    {
        char * data = *dataPtr2;
        delete [] data;
    }
}
void good()
{
    goodG2B();
}
int main(int argc, char * argv[])
{
    good();
    return 0;
}