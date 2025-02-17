// Condition-Mem-Leak-External-Function pattern checker
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


string File_Name;
int enter_bit = 1;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find an 'if' statement with a global function in the condition and a delete operator used on a variable in the body
StatementMatcher ifMatcher = ifStmt( hasCondition(implicitCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl()))))))),
                                     hasDescendant(compoundStmt(hasDescendant(cxxDeleteExpr(hasDescendant(declRefExpr(to(varDecl().bind("del_var")))))))) ).bind("if_stmt");

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
                    if(enter_bit == 1)
                    {
                        errs() << File_Name;
                        errs() << "\n" << "FP Located" << "\n";
                        enter_bit = 0;
                    }
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
    Finder.addMatcher(ifMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
