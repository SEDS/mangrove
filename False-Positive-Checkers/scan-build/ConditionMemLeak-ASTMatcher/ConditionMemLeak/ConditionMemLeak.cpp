#include <string>
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"


using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");

//AST Matcher to match the FP pattern
StatementMatcher IfMatcher = ifStmt(hasDescendant(
                               compoundStmt(hasDescendant(
                               callExpr(has(declRefExpr(
                               to(functionDecl(hasName("free")))))))))).bind("ifStmt");


class IfPrinter : public MatchFinder::MatchCallback {
public :
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const Stmt *IfS = Result.Nodes.getNodeAs<clang::Stmt>("ifStmt"))
    {
      errs() << "There is a memory free() operation being performed in an 'if' block" << "\n"
      << "This pattern may produce a false positive in SCA tools like CppCheck and scan-build!" << "\n"
      << "The AST for the pattern is as shown below:" << "\n";
      IfS->dumpColor();
    }
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  IfPrinter Printer;
  MatchFinder Finder;
  Finder.addMatcher(IfMatcher, &Printer);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}
