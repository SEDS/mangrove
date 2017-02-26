// Condition-Uninit-Var pattern checker
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
int use_start_line1 = 0;
int useMatcher1_flag = 0;
const NamedDecl *var_name3;
int decl_assign_start_line;
const NamedDecl *decl_assign_var;
int decl_assign_flag = 0;
int if_start_line;
int if_end_line;
const NamedDecl *rhs_var;
int if_flag = 0;
const NamedDecl *lhs_var;
const NamedDecl *fDecl1;
const NamedDecl *fDecl2;
const NamedDecl *fDecl3;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find statement with a memory allocation to a variable
StatementMatcher declAssignment = declStmt(hasAncestor(functionDecl().bind("fDecl1")), anyOf(has(varDecl(has(cStyleCastExpr(has(callExpr(has(ignoringParenImpCasts(declRefExpr(to(functionDecl(hasAnyName("__builtin_alloca","ALLOCA"))))))))))).bind("decl_assign_var")), has(varDecl().bind("decl_assign_var")) )).bind("decl_assign_stmt");

// AST matcher to find an 'if' statement with a variable initialization
StatementMatcher ifMatcher = ifStmt(hasAncestor(functionDecl().bind("fDecl2")), hasCondition( anyOf(ignoringParenImpCasts(declRefExpr(to(varDecl(hasGlobalStorage())))), binaryOperator(has(ignoringParenImpCasts(declRefExpr(to(varDecl(hasGlobalStorage()))))))) ),
                                     anyOf(hasDescendant(compoundStmt(hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("lhs_var"))))),hasRHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("rhs_var"))))))))), hasElse(compoundStmt(hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("lhs_var"))))),hasRHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("rhs_var"))))) )))), hasDescendant(compoundStmt(hasDescendant(binaryOperator( hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("lhs_var"))))), hasRHS(ignoringParenImpCasts(unaryOperator(hasDescendant(declRefExpr(to(varDecl().bind("rhs_var"))))))) )))) ) ).bind("if_stmt");

// AST matcher to find a statement with a function call
StatementMatcher useMatcher1 = stmt(anyOf(callExpr(hasAncestor(functionDecl().bind("fDecl3")), anyOf( hasArgument(1, ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_use"))))), hasAnyArgument(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_use"))))), hasAnyArgument(ignoringParenImpCasts(memberExpr(hasDescendant(declRefExpr(to(varDecl().bind("var_use"))))))), hasAnyArgument(ignoringParenImpCasts(hasDescendant(declRefExpr(to(varDecl().bind("var_use")))))) )
                                        ), binaryOperator(hasRHS(ignoringParenImpCasts(hasDescendant(declRefExpr(to(varDecl().bind("var_use"))))))) )).bind("use_stmt");


class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *decl_assign_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("decl_assign_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(decl_assign_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(decl_assign_stmt_node->getLocStart());
                    decl_assign_start_line = FullLocation1.getSpellingLineNumber();
                    if(const NamedDecl *decl_assign_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("decl_assign_var"))
                    {
                        decl_assign_var = decl_assign_var_node;
                        decl_assign_flag = 1;
                    }
                    if(const NamedDecl *fDecl1_node = Result.Nodes.getNodeAs<clang::NamedDecl>("fDecl1"))
                    {
                        fDecl1 = fDecl1_node;
                    }
                }
            }
            if(const Stmt *if_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt_node->getLocStart());
                    if_start_line = FullLocation1.getSpellingLineNumber();
                    FullSourceLoc FullLocation2 = Result.Context->getFullLoc(if_stmt_node->getLocEnd());
                    if_end_line = FullLocation2.getSpellingLineNumber();
                    if(const NamedDecl *lhs_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var"))
                    {
                        lhs_var = lhs_var_node;
                    }
                    if(const NamedDecl *rhs_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("rhs_var"))
                    {
                        rhs_var = rhs_var_node;
                        if_flag = 1;
                    }
                    if(const NamedDecl *fDecl2_node = Result.Nodes.getNodeAs<clang::NamedDecl>("fDecl2"))
                    {
                        fDecl2 = fDecl2_node;
                    }
                }
            }
            if(const Stmt *use_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("use_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(use_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(use_stmt_node->getLocStart());
                    use_start_line1 = FullLocation1.getSpellingLineNumber();
                    if(const NamedDecl *var_use_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_use"))
                    {
                        var_name3 = var_use_node;
                        useMatcher1_flag = 1;
                    }
                    if(const NamedDecl *fDecl3_node = Result.Nodes.getNodeAs<clang::NamedDecl>("fDecl3"))
                    {
                        fDecl3 = fDecl3_node;
                    }
                }
            }
            if(enter_bit == 1 && decl_assign_flag == 1 && if_flag == 1 && useMatcher1_flag == 1 && if_end_line < use_start_line1 && areSameVariable(fDecl1, fDecl2) && areSameVariable(fDecl1, fDecl3) && areSameVariable(lhs_var, var_name3))
            {
                errs() << "\n" << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                // Resetting the enter_bit in order to exit the program after the first instance of the pattern has been identified
                enter_bit = 0;
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

    Finder.addMatcher(declAssignment, &Printer);
    Finder.addMatcher(ifMatcher, &Printer);
    Finder.addMatcher(useMatcher1, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
