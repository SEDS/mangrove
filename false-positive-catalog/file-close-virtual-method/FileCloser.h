// Juliet CWE675_Duplicate_Operations_on_Resource__open_82.h

#include <unistd.h>  
#include <stdio.h>

namespace test { 
 
class FileCloserBase
{  
public:
	// Juliet uses a pure virtual method in the base class.
	// Both a pure virtual method and a non-pure virtual method (below) give the FP.
    virtual void action(int data) {};  
};  
 
class FileCloserSubclass : public FileCloserBase
{  
public:  
    void action(int data);  
};  
 
} 
