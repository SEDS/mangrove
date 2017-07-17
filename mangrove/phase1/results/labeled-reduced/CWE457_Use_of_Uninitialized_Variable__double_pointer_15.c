 static void goodG2B2()
{
    double * data;
    switch(6)
    {
    case 6:
        data = (double *)malloc(sizeof(double));
        *data = 5.0;
        break;
    default:
        printLine("Benign, fixed string");
        break;
    }
    switch(7)
    {
    case 7:
        printDoubleLine(*data);
        break;
    default:
        printLine("Benign, fixed string");
        break;
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printDoubleLine(*data);
*/

--tp-r--