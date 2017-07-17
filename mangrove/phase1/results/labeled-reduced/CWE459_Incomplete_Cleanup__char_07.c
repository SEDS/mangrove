 #include "std_testcase.h"
#define UNLINK unlink
#define FOPEN fopen
#define MKTEMP mktemp
static int staticFive = 5;
static void good2()
{
    if(staticFive==5)
    {
        {
            char * filename;
            char tmpl[] = "goodXXXXXX";
            FILE *pFile;
            filename = MKTEMP(tmpl);
            if (filename != NULL)
            {
                pFile = FOPEN(filename, "w");
                if (pFile != NULL)
                {
                    fprintf(pFile, "Temporary file");
                    fclose(pFile);
                    UNLINK(filename); 
                }
            }
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE459_Incomplete_Cleanup__char_07_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Call to function 'mktemp' is insecure as it always creates or uses insecure temporary file.  Use 'mkstemp' instead------            filename = MKTEMP(tmpl);
*/

--tp-r--