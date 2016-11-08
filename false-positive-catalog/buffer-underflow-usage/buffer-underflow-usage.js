// JavaScript version of buffer-underflow-usage FP pattern

/* global require */
/* global Buffer */

var BUFFER_SIZE = 10;

var fs = require('fs');
var buffer = Buffer.alloc(BUFFER_SIZE);

// Open file for reading.
var fd = fs.openSync('file.txt', 'r');

// Read 10 bytes into buffer, specifying write/read offsets to be 0.
//
// JSLint FP: none
// JSHint FP: none
// Closure Compiler FP: none
var bytesRead = fs.readSync(fd, buffer, 0, BUFFER_SIZE, 0);