// Custom code
// Structure: loop-flag

int helper (void) {
    bool flag = false;
    for (int i = 0; i < 10; i++) {
        if (flag) {
            // CodeSonar FP: Unreachable Data Flow. The highlighted code will not execute under any circumstances.
            //   This may be because of:
            //     (1) A function call that does not return
            //     (2) A test whose result is always the same (look for a preceding Redundant Condition warning)
            //     (3) A crashing bug (look for a preceding Null Pointer Dereference or Division By Zero warning)
            // scan-build FP: none
            // Cppcheck FP: none
            return 1;
        }
        flag = true;
    }
    // Note: CodeSonar gives a TP Unreachable Data Flow warning here.
    return 0;
}

int main(void) {
    // CodeSonar FP: Unreachable Data Flow. The highlighted code will not execute under any circumstances.
    //   This may be because of:
    //     (1) A function call that does not return
    //     (2) A test whose result is always the same (look for a preceding Redundant Condition warning)
    //     (3) A crashing bug (look for a preceding Null Pointer Dereference or Division By Zero warning)
    // scan-build FP: none
    // Cppcheck FP: none
    int result = helper();
    return 0;
}