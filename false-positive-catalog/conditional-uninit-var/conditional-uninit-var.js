// @flow
// JavaScript version of conditional-uninit-var FP pattern

var globalTrue = true;

function main() {
    var data;
    if (globalTrue) {
        data = 2;
    }

    /* Below we read the initialized `data` variable. No FP is flagged.
     *
     * Note: The following changes make no difference on whether a FP is flagged:
     *
     *   - The `data` variable is used in a computation instead of printed 
     *     (e.g. var foo = data + 5).
     *
     *   - The global variable is defined in an 
     *     external file and imported.
     *
     *   - The code is changed to a flawed version of the pattern. That is, 
     *     `globalTrue` is assigned the value `false`.
     */

    // JSLint FP: none
    // JSHint FP: none
    // Closure Compiler FP: none
    console.log(data);
}

main();