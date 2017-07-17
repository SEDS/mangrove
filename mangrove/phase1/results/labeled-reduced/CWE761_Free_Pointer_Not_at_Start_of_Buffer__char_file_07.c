 #include <wchar.h>
#define FILENAME "/tmp/file.txt"
#define SEARCH_CHAR 'S'
static int staticFive = 5;
static void goodB2G1()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    data[0] = '\0';
    {
        size_t dataLen = strlen(data);
        FILE * pFile;
        if (100-dataLen > 1)
        {
            pFile = fopen(FILENAME, "r");
            if (pFile != NULL)
            {
                if (fgets(data+dataLen, (int)(100-dataLen), pFile) == NULL)
                {
                    printLine("fgets() failed");
                    data[dataLen] = '\0';
                }
                fclose(pFile);
            }
        }
    }
    if(staticFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            size_t i;
            for (i=0; i < strlen(data); i++)
            {
                if (data[i] == SEARCH_CHAR)
                {
                    printLine("We have a match!");
                    break;
                }
            }
            free(data);
        }
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_file_07_good();
    printLine("Finished good()");
     0;
}
/* Warning description
The left operand of '==' is a garbage value------                if (data[i] == SEARCH_CHAR)
*/

--fp-r--