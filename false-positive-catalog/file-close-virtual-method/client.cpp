// Juliet CWE675_Duplicate_Operations_on_Resource__open_81a.cpp

#include "FileCloser.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

namespace test {
 
void createFile(void)
{  
    // CodeSonar FP: Leak. Data has gone out of scope and no longer references the resource of interest.
    // scan-build FP: none
    // Cppcheck FP: none
    int data = open("GoodSource_open.txt", O_RDWR|O_CREAT, S_IREAD|S_IWRITE);
    FileCloserBase * closeObj = new FileCloserSubclass();
 
    // Pass file descriptor to virtual method to close it.
    closeObj->action(data);  
    delete closeObj;  
}
}  

using namespace test;

int main(void) {
    createFile();
    return 0;
}
