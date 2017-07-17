 static int staticTrue = 1; 
static void goodG2B2()
{
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA(100*sizeof(char));
    if(staticTrue)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strcat(data, source);
        printLine(data);
    }
}
/* Warning description
Function call argument is an uninitialized value------        strcat(data, source);
*/

--fp-r--