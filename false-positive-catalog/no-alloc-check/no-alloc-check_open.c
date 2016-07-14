// Juliet CWE675_Duplicate_Operations_on_Resource__open_03.c
// Structure: no-alloc-check_open

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    // CodeSonar note: open() returns -1.
    int data = open("myfile.txt", O_RDWR|O_CREAT, S_IREAD|S_IWRITE);

    // CodeSonar warning: Negative file descriptor. File descriptor argument data has value -1. 'close()' will fail when called with a negative file descriptor.
    // scan-build warning: none
    // Cppcheck warning: none
    close(data);
    return 0;
}