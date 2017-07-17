#include <wchar.h>
typedef union
{
    int * unionFirst;
    int * unionSecond;
} CWE415_Double_Free__malloc_free_int_34_unionType;
static void goodG2B()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_34_unionType myUnion;
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    myUnion.unionFirst = data;
    {
        int * data = myUnion.unionSecond;
        free(data);
    }
}
void  main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );
    printLine("Calling good()...");
    CWE415_Double_Free__malloc_free_int_34_good();
    printLine("Finished good()");
     0;
}
/* Warning description
Potential leak of memory pointed to by 'myUnion.unionFirst'------        int * data = myUnion.unionSecond;
*/

--tp-r--