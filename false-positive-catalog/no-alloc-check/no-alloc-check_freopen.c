// Juliet CWE675_Duplicate_Operations_on_Resource__freopen_43.cpp
// Structure: no-alloc-check_freopen

#include <stdio.h>

int main(void)
{
	// CodeSonar note: fopen() returns NULL.
    FILE * data = fopen("myfile.txt", "w+");

    // CodeSonar warning: Null Pointer Dereference. The body of fclose() dereferences 'data', but it is NULL.
    // scan-build warning: none
    // Cppcheck warning: none
    fclose(data);
    return 0;
}