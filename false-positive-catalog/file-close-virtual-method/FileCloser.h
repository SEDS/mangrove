// Juliet CWE675_Duplicate_Operations_on_Resource__open_81.h

#include <unistd.h>  
#include <stdio.h>

namespace test { 
 
class FileCloserBase
{  
public:  
    virtual void action(int data) {};  
};  
 
class FileCloserSubclass : public FileCloserBase
{  
public:  
    void action(int data);  
};  
 
} 
