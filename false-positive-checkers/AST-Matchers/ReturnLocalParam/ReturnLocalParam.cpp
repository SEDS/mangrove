// Return-Local-Param pattern checker
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


// Name of this false positive checker.
#define CHECKER_NAME "ReturnLocalParam"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;

string File_Name;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher for a return statement that returns a parameter variable
StatementMatcher returnMatcher = returnStmt(has(ignoringParenImpCasts(declRefExpr(to(parmVarDecl(hasType(isAnyPointer())).bind("parm_var")))))).bind("return_stmt");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            // Isolating the return statement node
            if(const Stmt *return_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("return_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(return_stmt_node->getLocStart()))
                {
                    unsigned int lineNum = Result.Context->getSourceManager().getPresumedLineNumber(return_stmt_node->getLocStart());
                    errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << lineNum << "\n";
                }
            }
        }

    private:
        ASTContext *Context;
};

int main(int argc, const char **argv)
{
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    File_Name = argv[1];
    PatternFinder Printer;
    MatchFinder Finder;
    Finder.addMatcher(returnMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
