add_clang_executable(cker-condition-null-ptr-external-function
  ConditionNullPtrExternalFunction.cpp
  )

target_link_libraries(cker-condition-null-ptr-external-function
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
