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


using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;

Rewriter rewriter;
//Gets set when the 'if' condition statement has been traversed
int if_bit = 0;
//Gets set when a binary operator is encountered in the condition
int call_bit = 0;

class FindNamedClassVisitor
 : public RecursiveASTVisitor<FindNamedClassVisitor>
{
  public:
   explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context)
   {
    rewriter.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());
   }

 bool VisitDeclRefExpr (const DeclRefExpr *drexpr)
 {
  if(call_bit == 1)
  {
   drexpr->dump();
   const NamedDecl *ND = drexpr->getFoundDecl();
   std::string Vvarname = ND->getNameAsString();
   if(Vvarname == "free")
   errs() << "Function: " << "'" << Vvarname << "'" << " has been used in a condition!" << "\n";
   errs() << "FP detected!" << "\n";
   call_bit = 0;
  }
  return true;
 }

 bool VisitCallExpr(const CallExpr *call)
 {
  if(if_bit == 1)
  {
   if_bit = 0;
   call_bit = 1;
  }
  return true;
 }


 bool VisitIfStmt(IfStmt *st)
 {
  st->dumpColor();
  if_bit = 1;
    
  return true;
  }

  private:
   ASTContext *Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer
{
  public:
   explicit FindNamedClassConsumer(ASTContext *Context)
    : Visitor(Context)
  {
	
  }

  virtual void HandleTranslationUnit(clang::ASTContext &Context)
  {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());  
  }

 private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction
{
 public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile)
  {
    return std::unique_ptr<clang::ASTConsumer>(
        new FindNamedClassConsumer(&Compiler.getASTContext())); 
  }
};

int main(int argc, const char **argv)
{


 // parse the command-line args passed to your code
 static cl::OptionCategory MyToolCategory("My tool options");
 CommonOptionsParser op(argc, argv, MyToolCategory);        
 // create a new Clang Tool instance (a LibTooling environment)
 ClangTool Tool(op.getCompilations(), op.getSourcePathList());

 // run the Clang Tool, creating a new FrontendAction (explained below)
 int result = Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());

 return result;
}
