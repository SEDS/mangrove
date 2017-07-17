 static int staticFive = 5;
static void goodG2B1()
{
    int * data;
    if(staticFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = (int *)malloc(sizeof(int));
        *data = 5;
    }
    if(staticFive==5)
    {
        printIntLine(*data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printIntLine(*data);
*/

--tp-r--