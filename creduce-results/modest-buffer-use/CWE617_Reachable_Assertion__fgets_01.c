#include "std_testcase.h"
#define ASSERT_VALUE 5
#define CHAR_ARRAY_SIZE (3 * sizeof(data) + 2)
void CWE617_Reachable_Assertion__fgets_01_bad()
{
    int data;
    data = -1;
    {
        char inputBuffer[CHAR_ARRAY_SIZE] = "";
        if (fgets(inputBuffer, CHAR_ARRAY_SIZE, stdin) != NULL)
        {
            data = atoi(inputBuffer);
        }
        else
        {
            printLine("fgets() failed.");
        }
    }
    assert(data > ASSERT_VALUE);
}
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE617_Reachable_Assertion__fgets_01_good();
    printLine("Finished good()");
    printLine("Calling bad()...");
    CWE617_Reachable_Assertion__fgets_01_bad();
    printLine("Finished bad()");
    return 0;
}
