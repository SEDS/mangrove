add_clang_executable(cker-intermediate-function-call
  IntermediateFunctionCall.cpp
  )

target_link_libraries(cker-intermediate-function-call
  clangAnalysis
  clangAST
  clangBasic
  clangDriver
  clangEdit
  clangFrontend
  clangLex
  clangParse
  clangRewrite
  clangRewriteFrontend
  clangSema
  clangSerialization
  clangStaticAnalyzerFrontend
  clangTooling
  )
