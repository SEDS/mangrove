// Buffer-Store-Fgets pattern checker
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

int enter_bit = 1;
int if_start_line = 0;
int assign_start_line = 0;
std::string File_Name;
const NamedDecl *char_lit_var;
const NamedDecl *var_decl;
const NamedDecl *init_func;
const NamedDecl *parm_var;
const NamedDecl *var_lhs;
const NamedDecl *assign_func;
const NamedDecl *parm_var_assign;
const NamedDecl *parm_array_var;
const NamedDecl *index_var;



static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to identify data[0] = '\0'
StatementMatcher assignStmtMatcher1 = binaryOperator( hasLHS(arraySubscriptExpr( has(declRefExpr(to(varDecl().bind("char_lit_var")))),
                                                                                 has(integerLiteral(equals(0))) )),
                                                      hasRHS(implicitCastExpr(has(characterLiteral(equals(0))))) ).bind("assign_stmt1");

// AST matcher to identify variable declaration statement with a function's return value as initializer
StatementMatcher declStmtMatcher = stmt(has(varDecl(hasInitializer(callExpr( has(declRefExpr(to(functionDecl().bind("init_func")))),
                                                                 hasAnyArgument(declRefExpr(to(varDecl().bind("parm_var")))) ))).bind("var_decl") )).bind("decl_stmt");


// AST matcher to identify variable assignment statement with a function's return value as RHS value
StatementMatcher assignStmtMatcher2 = binaryOperator( hasLHS(declRefExpr(to(varDecl().bind("var_lhs")))),
                                        hasRHS(callExpr( has(declRefExpr(to(functionDecl().bind("assign_func")))),
                                        hasAnyArgument(declRefExpr(to(varDecl().bind("parm_var_assign")))) )),
                                        hasAncestor(ifStmt()) ).bind("assign_stmt2");

// AST matcher to identify data[dataLen-1] = '\0'
StatementMatcher assignStmtMatcher3 = ifStmt(has(compoundStmt(hasDescendant(binaryOperator( hasOperatorName("="),
                                                                                                 hasLHS(arraySubscriptExpr( has(declRefExpr(to(varDecl().bind("parm_array_var")))),
                                                                                                                            has(binaryOperator( hasOperatorName("-"),
                                                                                                                                                hasLHS(implicitCastExpr(has(declRefExpr(to(varDecl().bind("index_var")))))),
                                                                                                                                                hasRHS(implicitCastExpr(has(integerLiteral(equals(1))))) )) )),
                                                                                                 hasRHS(implicitCastExpr(has(characterLiteral(equals(0))))) ))))).bind("assign_stmt3");



class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *assign_stmt_node1 = Result.Nodes.getNodeAs<clang::Stmt>("assign_stmt1"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(assign_stmt_node1->getLocStart()))
                {
                    const NamedDecl *char_lit_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("char_lit_var");
                    char_lit_var = char_lit_var_node;
                }
            }
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
            if(const Stmt *assign_stmt_node2 = Result.Nodes.getNodeAs<clang::Stmt>("assign_stmt2"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(assign_stmt_node2->getLocStart()))
                {
                    const NamedDecl *var_lhs_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_lhs");
                    var_lhs = var_lhs_node;
                    const NamedDecl *assign_func_node = Result.Nodes.getNodeAs<clang::NamedDecl>("assign_func");
                    assign_func = assign_func_node;
                    const NamedDecl *parm_var_assign_node = Result.Nodes.getNodeAs<clang::NamedDecl>("parm_var_assign");
                    parm_var_assign = parm_var_assign_node;
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(assign_stmt_node2->getLocStart());
                    assign_start_line = FullLocation1.getSpellingLineNumber();
                }
            }
            if(const Stmt *assign_stmt_node3 = Result.Nodes.getNodeAs<clang::Stmt>("assign_stmt3"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(assign_stmt_node3->getLocStart()))
                {
                    const NamedDecl *parm_array_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("parm_array_var");
                    parm_array_var = parm_array_var_node;
                    const NamedDecl *index_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("index_var");
                    index_var = index_var_node;
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(assign_stmt_node3->getLocStart());
                    if_start_line = FullLocation1.getSpellingLineNumber();
                }
            }

            if(enter_bit == 1 && areSameVariable(char_lit_var, parm_var) && areSameVariable(var_decl, var_lhs) && areSameVariable(init_func, assign_func) && areSameVariable(parm_var, parm_var_assign) && areSameVariable(index_var, var_decl) && areSameVariable(parm_var, parm_array_var) && assign_start_line < if_start_line)
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
    Finder.addMatcher(assignStmtMatcher1, &Printer);
    Finder.addMatcher(declStmtMatcher, &Printer);
    Finder.addMatcher(assignStmtMatcher2, &Printer);
    Finder.addMatcher(assignStmtMatcher3, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
