#include "std_testcase.h"
static void goodB2G2()
{
    FILE * data;
    data = NULL;
    data = fopen("BadSource_fopen.txt", "w+");
    switch(6)
    {
    case 6:
        if (data != NULL)
        {
            fclose(data);
        }
        break;
    default:
        printLine("Benign, fixed string");
        break;
    }
}
int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_good();
    printLine("Finished good()");
    return 0;
}