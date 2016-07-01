#include "ClassCondition.h"

int main(void) {
	ClassCondition * myClass = new ClassCondition();
	myClass->test();
	delete myClass;
	return 0;
}