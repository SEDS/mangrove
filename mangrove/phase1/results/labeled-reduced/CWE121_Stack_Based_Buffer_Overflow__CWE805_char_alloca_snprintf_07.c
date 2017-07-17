 static int staticFive = 5;
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA(100*sizeof(char));
    if(staticFive==5)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        SNPRINTF(data, 100, "%s", source);
        printLine(data);
    }
}
/* Warning description
Function call argument is an uninitialized value------        SNPRINTF(data, 100, "%s", source);
*/

--fp-r--