// JavaScript version of null-array-access FP pattern

/* global Buffer */

var BUFFER_SIZE = 10;

// Allocate binary buffer with 0's and set first element to null character.
var buffer = Buffer.alloc(BUFFER_SIZE, 0, "binary");
buffer[0] = '\0';

for (var i = 0; i < buffer.length; i++) {
    /* Read the value of the buffer at this point.
     *
     * JSLint FP: none
     * JSHint FP: none
     * Closure Compiler FP: none
     *
     * Note: The following points make no difference to the warnings given by the 
     * tools:
     *
     *   - utf-8 vs. binary vs. ascii encoding
     *
     *   - Printing the buffer value instead of just reading it.
     */
    var value = buffer[i];
}