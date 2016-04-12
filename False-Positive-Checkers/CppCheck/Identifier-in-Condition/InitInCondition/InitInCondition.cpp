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
int binop_bit = 0;
//Gets set when the false positive pattern has been detected
int fp_bit = 0;
//Gets set when the false positive pattern is confirmed
int confirm_bit = 0;

class FindNamedClassVisitor
 : public RecursiveASTVisitor<FindNamedClassVisitor>
{
  public:
   explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context)
   {
    rewriter.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());
   }

 //Visiting binary operator node - if it exists
 bool VisitBinaryOperator (const BinaryOperator *BinOp)
 {
  if(BinOp->isRelationalOp() && if_bit == 1)
  {
   errs() << "Relational operator detected" << "\n";
   errs() << "AST: ";
   BinOp->dumpColor();
   if_bit = 0;
   binop_bit = 1;
  }
  return true;
 }

 bool VisitDeclRefExpr (const DeclRefExpr *drexpr)
 {
  //If the condition contains a binary operator
  if(binop_bit == 1)
  {
   errs() << "Variable used in the condition detected" << "\n";
   errs() << "AST: ";
   drexpr->dumpColor();
   binop_bit = 0;
   fp_bit = 1;
  }
  //If there is no binary operator in the conition
  else if(binop_bit == 0 && if_bit == 1)
  {
   errs() << "Condition does not have a binary operator" << "\n";
   errs() << "AST: ";
   drexpr->dumpColor();
   if_bit = 0;
   fp_bit = 1;
  }
  //If the node represents a variable in a location other than the if condition
  else
  {
   const NamedDecl *ND = drexpr->getFoundDecl();
   std::string Vvarname = ND->getNameAsString();
   const VarDecl *VD = dyn_cast<VarDecl>(ND);
   //Checks if the variable is initialized in the if-block
   if(!VD->isInitKnownICE() && fp_bit == 1)
   {
    errs() << "Variable " << Vvarname << " has now been initialized in the if-block" << "\n";
    for(int i = 0; i <= index; i++)
    {
     if(Vvarname == a[i])
      fp_bit = 0;
      confirm_bit = 1;
    }
    //If the FP pattern has been confirmed, then check if the variable has been used outside the if-block
    if(confirm_bit == 1)
    {
     for(int i = 0; i <= index; i++)
    {
     if(Vvarname == a[i])
     {
      errs() << "Variable " << Vvarname << " has been used outside the if-block" << "\n";
      errs() << "False positive pattern found!" << "\n";
     }
      confirm_bit = 0;
     }
    }
   }
  }
  return true;
 }
 //Visiting any declarations including variable declarations
 bool VisitNamedDecl (const NamedDecl *namedec)
 {
  if(const VarDecl *VD = dyn_cast<VarDecl>(namedec))
  {
   //If the declared variable has not been initialized then push it into the array
   if(!(VD->hasInit()))
   {
    std::string varname = namedec->getNameAsString();
    errs() << "Variable " << varname << " has not been initialized" << "\n";
    a[index] = varname;
    index++;
   }
   else
   {
    const Expr *InitVar = VD->getInit();
    Expr::NullPointerConstantValueDependence NPVD;
    //Checking if the variable is a NULL pointer
    if(Expr::NullPointerConstantKind NPC = InitVar->isNullPointerConstant(*Context, NPVD))
    {
     std::string varname = namedec->getNameAsString();
     errs() << "Variable " << varname << " is a NULL pointer" << "\n";
     a[index] = varname;
     index++;
    }
   }
  }
  return true;
 }

 bool VisitIfStmt(IfStmt *st) {
    if_bit = 1;
    Expr *cond = st->getCond();
    clang::Expr::EvalResult Result;
    bool res = 0;
    APValue apval;

    if(cond)
     {
      //The case where we verify if the condition is just an integer literal
      res = cond->EvaluateAsRValue(Result, *Context);
     }
    if(res)
     {
      apval = Result.Val;
      errs() << "Integer used in the condition" << "\n";
      errs() << "False positive not possible!" << "\n";
      if_bit = 0;
       apval.dump();
     }
    // The return value indicates whether we want the visitation to proceed.
    // Return false to stop the traversal of the AST.
    return true;
  }

  private:
   ASTContext *Context;
   std::array<std::string, 10> a;
   int index = 0;
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
