 static void goodG2B2()
{
    char * data;
    char dataGoodBuffer[100];
    if(globalReturnsTrue())
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strncat(data, source, 100);
        printLine(data);
    }
}
/* Warning description
Function call argument is an uninitialized value------        strncat(data, source, 100);
*/

--fp-r--