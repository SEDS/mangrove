// Intermediate-Function-Call pattern checker
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
#define CHECKER_NAME "IntermediateFunctionCall"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;


string File_Name;
int if_end_line = 0;
int call_start_line = 0;
int if_flag = 0;
int call_flag = 0;
const NamedDecl *var_assign;
const NamedDecl *var_use;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find an 'if' statement with a static global variable in the condition and variable assignment in the 'else' part
StatementMatcher ifMatcher = ifStmt( hasCondition(binaryOperator(hasDescendant(declRefExpr(to(varDecl(isStaticStorageClass(), hasGlobalStorage()).bind("cond_var1")))))),
                                     hasElse(compoundStmt(hasDescendant(binaryOperator(hasLHS(declRefExpr(to(varDecl().bind("var_assign")))))))) ).bind("if_stmt");

// AST matcher to find a function call that has the previously initialized variable as one of its arguments
StatementMatcher callMatcher = callExpr(hasAnyArgument(implicitCastExpr(hasDescendant(declRefExpr(to(varDecl().bind("var_use"))))))).bind("call_stmt");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            // Isolating the 'if' statement node
            if(const Stmt *if_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt_node->getLocStart()))
                {
                    if(const NamedDecl *var_assign_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_assign"))
                    {
                        var_assign = var_assign_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt_node->getLocEnd());
                        if_end_line = FullLocation1.getSpellingLineNumber();
                        if_flag = 1;
                    }
                }
            }
            // Isolating the use statement node
            if(const Stmt *call_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("call_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(call_stmt_node->getLocStart()))
                {
                    if(const NamedDecl *var_use_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_use"))
                    {
                        var_use = var_use_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(call_stmt_node->getLocStart());
                        call_start_line = FullLocation1.getSpellingLineNumber();
                        call_flag = 1;
                    }
                }
            }
            if(if_flag == 1 && call_flag == 1 && if_end_line < call_start_line && areSameVariable(var_assign, var_use))
            {
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << if_end_line << "," << call_start_line << "(end of 'if/else' block, use statement)\n";
            }

        }

        // Function to check if the two variable nodes are the same
        static bool areSameVariable(const NamedDecl *First, const NamedDecl *Second)
        {
            return First && Second && First->getCanonicalDecl() == Second->getCanonicalDecl();
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
    Finder.addMatcher(ifMatcher, &Printer);
    Finder.addMatcher(callMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
