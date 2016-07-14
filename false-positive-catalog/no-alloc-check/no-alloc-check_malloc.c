// Juliet CWE416_Use_After_Free__malloc_free_struct_18.c
// Structure: no-alloc-check_malloc

#include <stdlib.h>

int main(void)
{
	// CodeSonar note: malloc() returns NULL.
    char * data = (char *)malloc(sizeof(char));

    // CodeSonar warning: Null Pointer Dereference. 'Data' is dereferenced here, but it is NULL.
    // scan-build warning: none
    // Cppcheck warning: none
    *data = 'a';
    free(data);
    return 0;
}