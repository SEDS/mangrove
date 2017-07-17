 #define SRC_STRING "AAAAAAAAAA"
static int staticTrue = 1; 
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA((10+1)*sizeof(char));
    if(staticTrue)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        memmove(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
    }
}
/* Warning description
Function call argument is an uninitialized value------        memmove(data, source, (strlen(source) + 1) * sizeof(char));
*/

--fp-r--