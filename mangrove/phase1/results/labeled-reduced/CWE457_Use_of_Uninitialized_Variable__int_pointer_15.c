 static void goodG2B2()
{
    int * data;
    switch(6)
    {
    case 6:
        data = (int *)malloc(sizeof(int));
        *data = 5;
        break;
    default:
        printLine("Benign, fixed string");
        break;
    }
    switch(7)
    {
    case 7:
        printIntLine(*data);
        break;
    default:
        printLine("Benign, fixed string");
        break;
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printIntLine(*data);
*/

--tp-r--