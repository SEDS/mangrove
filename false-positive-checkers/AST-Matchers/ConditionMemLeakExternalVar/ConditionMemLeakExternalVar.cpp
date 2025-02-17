// Condition-Mem-Leak-External-Var pattern checker
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

string fileName;
const Stmt *IfS1;
const Stmt *IfS2;
int enter_bit = 1;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST Matcher expressions to match the FP pattern
// Matches an 'if' statement which has a memory free in it's body
StatementMatcher IfMatcher = ifStmt(hasDescendant(compoundStmt(hasDescendant(callExpr(hasDescendant(declRefExpr(to(functionDecl(hasName("free")))))))))).bind("ifStmt");

// Matches an 'if' statement which has a constatn global variable as it's condition expression
StatementMatcher if_global_const = ifStmt(hasCondition(opaqueValueExpr(hasType(booleanType())))).bind("if_glob_const");

// Callback for the AST matchers
class PatternFinder : public MatchFinder::MatchCallback {
    public :
        virtual void run(const MatchFinder::MatchResult &Result) {

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
        if(areSameExpr(Context,IfS1,IfS2) && enter_bit == 1)
        {
            errs() << "\n\n" << fileName << "\n";
            errs() << "FP Located" << "\n";

            IfS1 = 0;
            IfS2 = 0;
            enter_bit = 0;
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

int main(int argc, const char **argv) {
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    fileName = argv[1];
    PatternFinder PatFinder;
    MatchFinder Finder;

    // Add the AST matcher expressions to the match callback
    Finder.addMatcher(IfMatcher, &PatFinder);
    Finder.addMatcher(if_global_const, &PatFinder);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
