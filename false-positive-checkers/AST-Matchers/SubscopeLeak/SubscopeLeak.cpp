// Subscope-Leak pattern checker
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

// False positive pattern name.
#define CHECKER_NAME "SubscopeLeak" 

string File_Name;
int new_start_line;
int new_flag = 0;
int scope_start_line;
int scope_flag = 0;
const NamedDecl *lhs_var;
const NamedDecl *del_var;
int lhs_var_line;
int del_var_line;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to identify a variable allocation using 'new'
StatementMatcher newStmtMatcher = declStmt(has(varDecl(has(ignoringParenImpCasts(unaryOperator()))).bind("lhs_var"))).bind("new_stmt");

// AST matcher to identify a delete statement within a nested scope
StatementMatcher scopeMatcher = compoundStmt( anyOf( has(cxxDeleteExpr(ignoringParenImpCasts(hasDescendant(declRefExpr(to(varDecl().bind("del_var"))))))), has(callExpr(has(ignoringParenImpCasts(declRefExpr(to(functionDecl(hasName("free")))))), hasAnyArgument(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("del_var"))))))) ), unless(hasParent(functionDecl())), unless(hasParent(ifStmt())), unless(hasParent(forStmt())), unless(hasParent(whileStmt())) ).bind("scope_stmt");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {

            if(const Stmt *new_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("new_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(new_stmt_node->getLocStart()))
                {
                    if(const NamedDecl *lhs_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var"))
                    {
                        lhs_var = lhs_var_node;
                        new_flag = 1;
                        FullSourceLoc FullLocation2 = Result.Context->getFullLoc(lhs_var->getLocStart());
                        lhs_var_line = FullLocation2.getSpellingLineNumber();
                    }
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(new_stmt_node->getLocStart());
                    new_start_line = FullLocation1.getSpellingLineNumber();
                }
            }
            // Isolating the sub-scoped delete statement
            if(const Stmt *scope_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("scope_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(scope_stmt_node->getLocStart()))
                {
                    if(const NamedDecl *del_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("del_var"))
                    {
                        del_var = del_var_node;
                        scope_flag = 1;
                        FullSourceLoc FullLocation2 = Result.Context->getFullLoc(del_var->getLocStart());
                        del_var_line = FullLocation2.getSpellingLineNumber();
                    }
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(scope_stmt_node->getLocStart());
                    scope_start_line = FullLocation1.getSpellingLineNumber();
                }
            }
            if(areSameVariable(lhs_var, del_var) && new_flag == 1 && scope_flag == 1)
            {
                unsigned int lineNum = Result.Context->getSourceManager().getPresumedLineNumber(scope_stmt_node->getLocStart());
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << lineNum << "\n";
            }
        }

        // Function to check if the two variable nodes are the same
        // Used the example provided by: http://clang.llvm.org/docs/LibASTMatchersTutorial.html
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

    Finder.addMatcher(newStmtMatcher, &Printer);
    Finder.addMatcher(scopeMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
