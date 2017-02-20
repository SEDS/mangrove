// Condition-Mem-Leak pattern checker
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
#define CHECKER_NAME "ConditionMemLeak"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;

string File_Name;
const Stmt *IfS1;
const Stmt *IfS2;
const NamedDecl *var_free;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST Matcher expressions to match the FP pattern
// Matches an 'if' statement which has a memory free or delete in its body
StatementMatcher IfMatcher = ifStmt(hasDescendant(compoundStmt( anyOf(hasDescendant(callExpr(hasAnyArgument(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_free"))))), hasDescendant(declRefExpr(to(functionDecl(hasName("free")))))) ), hasDescendant(cxxDeleteExpr()) )))).bind("ifStmt");


// Matches an 'if' statement which has a global variable as its condition expression
StatementMatcher if_global_const = ifStmt(anyOf(hasCondition(ignoringParenImpCasts(declRefExpr(to(varDecl( anyOf((hasGlobalStorage(), hasInitializer(integerLiteral(unless(equals(0))))), (hasGlobalStorage(), hasExternalFormalLinkage())) ))))), hasCondition(binaryOperator(has(ignoringParenImpCasts(declRefExpr(to(varDecl( anyOf((hasGlobalStorage(), hasInitializer(integerLiteral(unless(equals(0))))), (hasGlobalStorage(), hasExternalFormalLinkage())) ))))))))).bind("if_glob_const");

// Callback for the AST matchers
class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            Context = Result.Context;

            // Isolate the node identified by the AST matcher named 'IfMatcher'
            if(const Stmt *var1 = Result.Nodes.getNodeAs<clang::Stmt>("if_glob_const"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(var1->getLocStart()))
                {
                    IfS1 = var1;
                }
            }
            // Isolate the node identified by the AST matcher named 'if_global_const'
            if(const Stmt *var2 = Result.Nodes.getNodeAs<clang::Stmt>("ifStmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(var2->getLocStart()))
                {
                    IfS2 = var2;
                }
            }
            // If both the statement matchers match the same statement we conclude that the FP pattern has been found
            if(areSameExpr(Context,IfS1,IfS2))
            {
                unsigned int lineNum = Result.Context->getSourceManager().getPresumedLineNumber(IfS1->getLocStart());
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << lineNum << " (IF statement located)\n";

                IfS1 = 0;
                IfS2 = 0;
                return;
            }
        }

        // Function to check if the expressions are the same
        static bool areSameExpr(ASTContext *Context, const Stmt *First, const Stmt *Second)
        {
            if (!First || !Second)
                return false;
            llvm::FoldingSetNodeID FirstID, SecondID;
            First->Profile(FirstID, *Context, true);
            Second->Profile(SecondID, *Context, true);
            return FirstID == SecondID;
        }

    private:
        ASTContext *Context;
};

int main(int argc, const char **argv)
{
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    File_Name = argv[1];
    PatternFinder PatFinder;
    MatchFinder Finder;

    // Add the AST matcher expressions to the match callback
    Finder.addMatcher(IfMatcher, &PatFinder);
    Finder.addMatcher(if_global_const, &PatFinder);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
