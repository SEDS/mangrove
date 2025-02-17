// Buffer-Underflow-Usage pattern checker
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
#define CHECKER_NAME "BufferUnderflowUsage"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;


string File_Name;
int decl_start_line;
int call_start_line;
int decl_flag = 0;
int use_flag = 0;
const NamedDecl *var_decl;
const NamedDecl *var_use;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to identify the delaration of a variable with a zero length string initialized to it
StatementMatcher declMatcher = declStmt(has(varDecl(has(stringLiteral(hasSize(0)))).bind("var_decl"))).bind("decl_stmt");

// AST matcher to identify an 'fgets' function call that uses the previously declared variable
StatementMatcher callMatcher = callExpr(has(ignoringParenImpCasts(declRefExpr(to(functionDecl(hasName("fgets")))))),
                                        hasAnyArgument(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_use")))))).bind("call_stmt");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            // Isolating the declaration statement node
            if(const Stmt *decl_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("decl_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(decl_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(decl_stmt_node->getLocStart());
                    decl_start_line = FullLocation1.getSpellingLineNumber();

                    if(const NamedDecl *var_decl_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_decl"))
                    {
                        var_decl = var_decl_node;
                        decl_flag = 1;
                    }
                }
            }
            // Isolating the use statement node
            if(const Stmt *call_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("call_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(call_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(call_stmt_node->getLocStart());
                    call_start_line = FullLocation1.getSpellingLineNumber();

                    if(const NamedDecl *var_use_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_use"))
                    {
                        var_use = var_use_node;
                        use_flag = 1;
                    }
                }
            }
            if(decl_flag == 1 && use_flag == 1 && decl_start_line < call_start_line && areSameVariable(var_decl, var_use))
            {
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << decl_start_line << "\n";
            }
        }
        // Function to check if the variables are the same
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
    Finder.addMatcher(declMatcher, &Printer);
    Finder.addMatcher(callMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
