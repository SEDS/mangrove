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
#include "varDeclASTMatcher.h"
#include "memAllocASTMatcher.h"
#include "ifGlobAssignASTMatcher.h"
#include "ifGlobConstASTMatcher.h"
#include "useStmtASTMatcher.h"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;

std::string File_Name;
int for_start_line;
int binOp_start_line;
int enter_bit = 1;
const NamedDecl *var_name1;
const NamedDecl *var_name2;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// Statement matcher to match the statement data[0] = '\0'
StatementMatcher nullArrayAccess = binaryOperator( hasLHS(arraySubscriptExpr(has(declRefExpr(to(varDecl().bind("var_decl")))),
                                                                              has(integerLiteral(equals(0))) )),
                                                   hasRHS(implicitCastExpr(has(characterLiteral(equals(0))))) ).bind("bin_op");
// Statement matcher to match a 'for' statement with data[i] being used in the body
StatementMatcher forMatcher = forStmt( hasDescendant(compoundStmt(hasDescendant(arraySubscriptExpr( hasDescendant(implicitCastExpr(has(declRefExpr(to(varDecl().bind("var_use"))))))
                                                                                                     )))) ).bind("for_stmt");

// Callback for the AST matchers
class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *bin_op_node = Result.Nodes.getNodeAs<clang::Stmt>("bin_op"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(bin_op_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(bin_op_node->getLocStart());
                    binOp_start_line = FullLocation1.getSpellingLineNumber();
                    if(const NamedDecl *var_decl = Result.Nodes.getNodeAs<clang::NamedDecl>("var_decl"))
                    {
                        var_name1 = var_decl;
                    }
                }
            }
 
            if(const Stmt *for_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("for_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(for_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(for_stmt_node->getLocStart());
                    for_start_line = FullLocation1.getSpellingLineNumber();

                    if(const NamedDecl *var_use = Result.Nodes.getNodeAs<clang::NamedDecl>("var_use"))
                    {
                        var_name2 = var_use;
                    }
                }
            } 

            // Function to check if the 2 variables are the same
            if(areSameVariable(var_name1, var_name2) && binOp_start_line <= for_start_line && enter_bit == 1)
            {
                errs() << "\n" << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                enter_bit = 0;
                return;
            }
        }

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
    PatternFinder PatFinder;
    MatchFinder Finder;
    Finder.addMatcher(nullArrayAccess, &PatFinder);
    Finder.addMatcher(forMatcher, &PatFinder);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
