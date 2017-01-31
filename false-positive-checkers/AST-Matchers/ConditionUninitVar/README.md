# False positive pattern: Condition-Uninit-Var

This repository includes the companion files for this [Clang LibTooling Example](http://kevinaboos.blogspot.com/2013/07/clang-tutorial-part-ii-libtooling.html).

Checkout this repository

       $ git clone https://github.iu.edu/SEDS/mangrove.git

Change directory to where you want llvm directory placed

	$ mkdir static_analysis
	$ cd static_analysis

Create a setup directory

        $ mkdir setup

And copy the contents of the folder 'ConditionUninitVar' into this(setup) folder

Run the setup script to download llvm/clang source

	$ sh setup/setup.sh

Next we need to tell Clang about our new tool:

	$ cd static_analysis/llvm/tools/clang/tools

	add 'ConditionUninitVar' to PARALLEL_DIRS :- in the Makefile
	
	add 'add_clang_subdirectory(ConditionUninitVar)' to CMakeLists.txt

Build llvm using cmake to generate files

	$ cd static_analysis 
	$ mkdir -p build
	$ cd build
	$ cmake -DCMAKE_BUILD_TYPE=RELEASE ../llvm/
	$ make -j4

Run the script run_clang-reduce.sh to use our new tool on some sample c source code:

	$ cd static_analysis/setup
	$ chmod +x run_clang-tool.sh
	$ ./run_clang-tool.sh
