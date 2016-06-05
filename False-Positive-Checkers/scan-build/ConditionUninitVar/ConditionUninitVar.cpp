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

StatementMatcher declMatcher = ifStmt(hasCondition(has(declRefExpr(to(varDecl(hasGlobalStorage())))))).bind("declSt");
StatementMatcher declMatcher2 = ifStmt(hasDescendant(declRefExpr(to(varDecl(hasInitializer(anything())))))).bind("declStmt");
StatementMatcher declMatcher3 = ifStmt(isExpansionInMainFile()).bind("declMain");

int line1 = 1;
int line2 = 2;
int line3 = 3;
int col1 = 1;
int col2 = 2;
int col3 = 3;

class IfPrinter : public MatchFinder::MatchCallback
{
 public :
   virtual void run(const MatchFinder::MatchResult &Result)
   {
    if(const Stmt *IfS1 = Result.Nodes.getNodeAs<clang::Stmt>("declSt"))
    {
      IfS1->dumpColor();
      FullSourceLoc FullLocation1 = Result.Context->getFullLoc(IfS1->getLocStart());
      line1 = FullLocation1.getSpellingLineNumber();
      col1 = FullLocation1.getSpellingColumnNumber();
    }
    if(const Stmt *IfS2 = Result.Nodes.getNodeAs<clang::Stmt>("declStmt"))
    {
      FullSourceLoc FullLocation2 = Result.Context->getFullLoc(IfS2->getLocStart());
      line2 = FullLocation2.getSpellingLineNumber();
      col2 = FullLocation2.getSpellingColumnNumber();
    }
    if(const Stmt *IfS3 = Result.Nodes.getNodeAs<clang::Stmt>("declMain"))
    {
      FullSourceLoc FullLocation3 = Result.Context->getFullLoc(IfS3->getLocStart());
      line3 = FullLocation3.getSpellingLineNumber();
      col3 = FullLocation3.getSpellingColumnNumber();
    }
    if ((line1 == line2) && (col1 == col2) && (line1 == line3) && (col1 == col3))
    {
      errs() << "A variable has been intialized inside an 'if' block with a global condition variable" << "\n" << "This may generate a false positive in SCA tools!" << "\n";
    }
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
  errs() << "\n\n\n\n" << argv[1] << "\n";
  IfPrinter Printer;
  MatchFinder Finder;
  Finder.addMatcher(declMatcher, &Printer);
  Finder.addMatcher(declMatcher2, &Printer);
  Finder.addMatcher(declMatcher3, &Printer);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}
