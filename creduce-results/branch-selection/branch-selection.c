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
    }
}
void CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_good()
{
    goodB2G2();
}
int main(int argc, char * argv[])
{
    CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_good();
    return 0;
}