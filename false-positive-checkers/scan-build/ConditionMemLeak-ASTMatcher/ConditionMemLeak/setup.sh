#!/usr/bin/env zsh

# script to initialize the llvm toolchain

llvm='http://llvm.org/svn/llvm-project'

# trunk is main line of dev in SVN

version='trunk'

# version='branches/release_37'

echo "––––––––––––llvm––––––––––––"

# contains seperated source and build folder

# checkout llvm

svn co $llvm/llvm/$version/ llvm

# checkout clang

tools='llvm/tools'

svn co $llvm/cfe/$version/ $tools/clang

# checkout extra clang tools

ctools='llvm/tools/clang/tools'

svn co $llvm/clang-tools-extra/$version/ $ctools/extra

# checkout compiler-RT

projects='llvm/projects'

svn co $llvm/compiler-rt/$version/ $projects/compiler-rt

mkdir llvm/tools/clang/tools/ConditionMemLeak
mv setup/Makefile llvm/tools/clang/tools/ConditionMemLeak
mv setup/ClangReduce.cpp llvm/tools/clang/tools/ConditionMemLeak
mv setup/CMakeLists.txt llvm/tools/clang/tools/ConditionMemLeak
