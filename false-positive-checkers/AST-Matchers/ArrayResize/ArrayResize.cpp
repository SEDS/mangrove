// Array-Resize pattern checker
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
const NamedDecl *var_decl;
const NamedDecl *init_func;
const NamedDecl *parm_var;

const NamedDecl *var_lhs;
const NamedDecl *assign_func;
const NamedDecl *parm_var_assign;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");


// AST matcher to identify variable declaration statement with a function's return value as initializer
StatementMatcher declStmtMatcher = declStmt(has(varDecl(hasInitializer(callExpr( hasDescendant(declRefExpr(to(functionDecl().bind("init_func")))),
                                                                                 hasAnyArgument(implicitCastExpr(hasDescendant(declRefExpr(to(parmVarDecl().bind("parm_var")))))) ))).bind("var_decl") )).bind("decl_stmt");

// AST matcher to identify variable assignment statement with a function's return value as RHS value
StatementMatcher assignStmtMatcher = binaryOperator( hasLHS(declRefExpr(to(varDecl().bind("var_lhs")))),
                                                     hasRHS(callExpr( hasDescendant(declRefExpr(to(functionDecl().bind("assign_func")))),
                                                                      hasAnyArgument(implicitCastExpr(hasDescendant(declRefExpr(to(parmVarDecl().bind("parm_var_assign")))))) )),
                                                     hasAncestor(ifStmt()) ).bind("assign_stmt");


class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *decl_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("decl_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(decl_stmt_node->getLocStart()))
                {
                    const NamedDecl *var_decl_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_decl");
                    var_decl = var_decl_node;
                    const NamedDecl *init_func_node = Result.Nodes.getNodeAs<clang::NamedDecl>("init_func");
                    init_func = init_func_node;
                    const NamedDecl *parm_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("parm_var");
                    parm_var = parm_var_node;
                }
            }
            if(const Stmt *assign_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("assign_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(assign_stmt_node->getLocStart()))
                {
                    const NamedDecl *var_lhs_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_lhs");
                    var_lhs = var_lhs_node;
                    const NamedDecl *assign_func_node = Result.Nodes.getNodeAs<clang::NamedDecl>("assign_func");
                    assign_func = assign_func_node;
                    const NamedDecl *parm_var_assign_node = Result.Nodes.getNodeAs<clang::NamedDecl>("parm_var_assign");
                    parm_var_assign = parm_var_assign_node;
                }
            }

            if(enter_bit == 1 && areSameVariable(var_decl, var_lhs) && areSameVariable(init_func, assign_func) && areSameVariable(parm_var, parm_var_assign))
            {
                errs() << "\n" << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                enter_bit = 0;
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
    Finder.addMatcher(declStmtMatcher, &Printer);
    Finder.addMatcher(assignStmtMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
