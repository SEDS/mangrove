static int staticFive = 5;
static void goodG2B1()
{
    int * data;
    int dataUninitArray[10];
    data = dataUninitArray;
    if(staticFive!=5)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                data[i] = i;
            }
        }
    }
    if(staticFive==5)
    {
        {
            int i;
            for(i=0; i<10; i++)
            {
                printIntLine(data[i]);
            }
        }
    }
}
/* Warning description
Function call argument is an uninitialized value------                printIntLine(data[i]);
*/

--fp-r--