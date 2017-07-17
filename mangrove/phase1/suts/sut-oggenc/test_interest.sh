#!/bin/bash

var=$(scan-build gcc -c oggenc.c 2>&1 | cat);
if [[ "$var" == *"error: "* ]]; then
   exit 1;
fi

if [[ "$var" != *": warning: Access to field 'name' results in a dereference of a null pointer (loaded from variable 'p')"* ]]; then
   exit 1;
fi

if [[ "$var" != *"for (p = longopts, option_index = 0; p->name;"* ]]; then
exit 1;
fi

exit 0;
