#ifndef OMITBAD
static void good2()
{
    {
    {
        int array[5] = { 1, 2, 3, 4, 5 };
        char *pointer = (char *)array;
        int toPrint = (int) (*(pointer+(2*sizeof(int))));
    }
    }
}
#endif
