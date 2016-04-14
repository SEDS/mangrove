#include "std_testcase.h"
#define CHAR_ARRAY_SIZE (3 * sizeof(data) + 2)
void CWE617_Reachable_Assertion__fgets_01_bad()
{
    int data;
    data = -1;
    char inputBuffer[CHAR_ARRAY_SIZE] = "";
    if (fgets(inputBuffer, CHAR_ARRAY_SIZE, stdin) != NULL)
    {
        data = atoi(inputBuffer);
    }
}
int main(int argc, char * argv[])
{
    CWE617_Reachable_Assertion__fgets_01_bad();
    return 0;
}