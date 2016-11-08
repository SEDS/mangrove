// JavaScript version of alloc-using-global-var FP pattern

/* global Buffer */

var globalSize;

function goodG2BSink() {
    var size = globalSize;
    var i;

    var intBuffer = Buffer.alloc(size);
    for (i = 0; i < size; i++) {
        intBuffer[i] = 7;
    }
    /* Access the first element. 
     *
     * JSLint FP: none
     * JSHint FP: none
     * Closure Compiler FP: none
     *
     * Note: The following points make no difference to the tool warnings:
     *
     *   - Whether the `globalSize` variable is defined in an external file and
     *     imported.
     *
     *   - Whether the `globalSize` is assigned an unreasonably large value 
     *     instead of 10.
     */
    console.log(intBuffer[0]);
}

function main() {
    var size = 10;
    globalSize = size;
    goodG2BSink();
}

main();