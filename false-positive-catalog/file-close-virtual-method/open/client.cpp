// Juliet CWE675_Duplicate_Operations_on_Resource__open_81a.cpp

#include "FileCloser.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

namespace test {
 
void createFile(void)
{  
    int data = open("GoodSource_open.txt", O_RDWR|O_CREAT, S_IREAD|S_IWRITE);
    FileCloserBase * closeObj = new FileCloserSubclass();
 
    closeObj->action(data);  
    delete closeObj;  
}

}  


//using namespace test;

int main(void) {
    test::createFile();
    return 0;
}
