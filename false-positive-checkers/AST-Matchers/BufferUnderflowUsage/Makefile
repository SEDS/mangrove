CLANG_LEVEL := ../..

TOOLNAME = buffer-underflow-usage

SOURCES := BufferUnderflowUsage.cpp  

include $(CLANG_LEVEL)/../../Makefile.config

LINK_COMPONENTS := $(TARGETS_TO_BUILD) asmparser bitreader support mc option
 
USEDLIBS = clangFrontend.a clangSerialization.a clangDriver.a \
           clangTooling.a clangParse.a clangSema.a \
           clangAnalysis.a clangRewriteFrontend.a clangRewrite.a \
	   clangEdit.a clangAST.a clangLex.a clangBasic.a

include $(CLANG_LEVEL)/Makefile
