#ifndef _ARRAY_H_
#define _ARRAY_H_

class ClassCondition {
public:
	// Initialize the private variable to 1 (true).
	ClassCondition(void);

	// Perform a test on the private variable.
	void test(void);

private:
	int alwaysTrue_;
};


#endif