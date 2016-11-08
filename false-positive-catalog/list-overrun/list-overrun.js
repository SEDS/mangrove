// JavaScript version of list-overrun FP pattern

function good(dataArray) {
    // Pop the last element off of the array.
    //
    // JSLint FP: none
    // JSHint FP: none
    // Closure Compiler FP: none
    //
    // Note: It does not make any difference to the tool warnings if the code
    // is changed to a flawed version (that is, the `good()` function is passed 
    // an empty array). In fact, JavaScript does not consider popping an empty
    // array as an exception. It simply returns `undefined`.

    var data = dataArray.pop();
}

function main() {
    var str = "Good";
    var dataArray = [str];
    good(dataArray);
}

main();