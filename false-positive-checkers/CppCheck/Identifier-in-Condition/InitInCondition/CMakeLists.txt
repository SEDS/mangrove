add_clang_executable(initialization-in-condition
  InitInCondition.cpp
  )

target_link_libraries(initialization-in-condition
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
