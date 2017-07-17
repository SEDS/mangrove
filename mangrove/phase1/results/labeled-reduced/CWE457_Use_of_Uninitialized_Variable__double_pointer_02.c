 static void goodG2B2()
{
    double * data;
    if(1)
    {
        data = (double *)malloc(sizeof(double));
        *data = 5.0;
    }
    if(1)
    {
        printDoubleLine(*data);
    }
}
/* Warning description
Potential leak of memory pointed to by 'data'------        printDoubleLine(*data);
*/

--tp-r--