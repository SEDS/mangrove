#define SRC_STRING "AAAAAAAAAA"
static int staticTrue = 1; 
static void goodG2B2()
{
    char * data,  * dataGoodBuffer = (char *)ALLOCA((10+1)*sizeof(char));
    if(staticTrue)
    {
        data = dataGoodBuffer;
        data[0] = '\0'; 
    }
    {
        char source[10+1] = SRC_STRING;
        strcpy(data, source);
        printLine(data);
    }
}