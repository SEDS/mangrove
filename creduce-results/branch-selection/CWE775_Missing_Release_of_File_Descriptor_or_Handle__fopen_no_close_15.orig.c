/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15.c
Label Definition File: CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close.label.xml
Template File: source-sinks-15.tmpl.c
*/
/*
 * @description
 * CWE: 775 Missing Release of File Descriptor or Handle After Effective Lifetime
 * BadSource:  Open a file using fopen()
 * Sinks:
 *    GoodSink: Close the file using fclose()
 *    BadSink : Do not close file
 * Flow Variant: 15 Control flow: switch(6)
 *
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_bad()
{
    FILE * data;
    data = NULL;
    /* POTENTIAL FLAW: Open a file without closing it */
    data = fopen("BadSource_fopen.txt", "w+");
    switch(6)
    {
    case 6:
        /* FLAW: No attempt to close the file */
        ; /* empty statement needed for some flow variants */
        break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G1() - use badsource and goodsink by changing the switch to switch(5) */
static void goodB2G1()
{
    FILE * data;
    data = NULL;
    /* POTENTIAL FLAW: Open a file without closing it */
    data = fopen("BadSource_fopen.txt", "w+");
    switch(5)
    {
    case 6:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    default:
        /* FIX: If the file is still opened, close it */
        if (data != NULL)
        {
            fclose(data);
        }
        break;
    }
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the switch */
static void goodB2G2()
{
    FILE * data;
    data = NULL;
    /* POTENTIAL FLAW: Open a file without closing it */
    data = fopen("BadSource_fopen.txt", "w+");
    switch(6)
    {
    case 6:
        /* FIX: If the file is still opened, close it */
        if (data != NULL)
        {
            fclose(data);
        }
        break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}

void CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_good()
{
    goodB2G1();
    goodB2G2();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE775_Missing_Release_of_File_Descriptor_or_Handle__fopen_no_close_15_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif