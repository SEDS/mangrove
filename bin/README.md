# Mangrove

Mangrove implementation just for code reduction.

## Directory structure

* `./Mangrove.py` - main program
* `./Mangrove.conf` - configuration file
* `./lib` - libraries
  * `./lib/Support` - general libraries
  * `./lib/Reduction` - libraries to perform code reduction
  * `./lib/Tools` - libraries to run the SCA tools
  * `./lib/Validation` - libraries to check whether a code snippet produces a certain warning


## Example to run it:

```
python Mangrove.py --fps-file juliet_12_single_example.xml CppCheck --compiler g++ --options '-I ../../../mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcasesupport/'
```

or

```
python Mangrove.py --fname /Users/mlmarenchino/Development/VirtualBoxVMs/SharedFolder/code/mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcases/CWE843_Type_Confusion/CWE843_Type_Confusion__short_52a.c --line 55 --info "Dead pointer usage. Pointer 'data' is dead if it has been assigned '&amp;buf' at line 53." CppCheck --compiler /usr/bin/clang --options '-I/Users/mlmarenchino/Development/VirtualBoxVMs/SharedFolder/code/mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcasesupport/ -I/Users/mlmarenchino/Development/VirtualBoxVMs/SharedFolder/code/mangrove-umd/SCATE/test-cases/NIST_Cpp_1_2/testcases/CWE843_Type_Confusion/'
```

