// Juliet CWE675_Duplicate_Operations_on_Resource__open_82_goodG2B.cpp

#include "FileCloser.h"
#include <unistd.h>
 
namespace test { 

void FileCloserSubclass::action(int data)  
{  
    close(data);  
}
  
}
