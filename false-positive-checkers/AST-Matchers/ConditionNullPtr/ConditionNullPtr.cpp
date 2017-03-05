// Condition-Null-Ptr pattern checker
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

// Name of this false positive checker.
#define CHECKER_NAME "ConditionNullPtr" 

string File_Name;
int if_end_line1 = 0;
int use_start_line1 = 0;
int ifMatcher1_flag = 0;
int useMatcher1_flag = 0;
const NamedDecl *var_name1;
const NamedDecl *var_name2;
const NamedDecl *decl_name1;
const NamedDecl *decl_name2;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find an 'if' statement with a memory allocation to a variable
StatementMatcher ifMatcher = ifStmt(hasCondition( anyOf(ignoringParenImpCasts(binaryOperator(has(ignoringParenImpCasts(declRefExpr(to(varDecl(hasGlobalStorage()).bind("cond_var"))))))), ignoringParenImpCasts(declRefExpr(to(varDecl(hasGlobalStorage()).bind("cond_var")))) ) ),
                                hasDescendant(compoundStmt( anyOf( hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_assign"))))), hasRHS(cStyleCastExpr(hasDescendant(callExpr(has(ignoringParenImpCasts(declRefExpr(to(functionDecl(hasAnyName("ALLOCA", "__builtin_alloca", "malloc")))))))))))), hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_assign"))))), hasRHS(ignoringParenImpCasts(declRefExpr())))), hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_assign"))))), hasRHS(ignoringParenImpCasts(unaryOperator())))), hasDescendant(binaryOperator(hasLHS(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_assign"))))), hasRHS(ignoringParenImpCasts(cxxNewExpr()))))) )),  
                                hasAncestor(functionDecl().bind("decl_name1"))).bind("if_stmt");

// AST matcher to find a use of the previously initialized variable
StatementMatcher useMatcher = callExpr( anyOf(hasAnyArgument(ignoringParenImpCasts(declRefExpr(to(varDecl().bind("var_use"))))), hasAnyArgument(ignoringParenImpCasts(hasDescendant(declRefExpr(to(varDecl().bind("var_use")))))), hasAnyArgument(ignoringParenImpCasts(unaryOperator(hasDescendant(declRefExpr(to(varDecl().bind("var_use"))))))) ),
                                        hasAncestor(functionDecl().bind("decl_name2")) ).bind("use_stmt");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *if_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt_node->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt_node->getLocEnd());
                    if_end_line1 = FullLocation1.getSpellingLineNumber();
                    if(const NamedDecl *var_assign_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_assign"))
                    {
                        if(const NamedDecl *decl_name_node1 = Result.Nodes.getNodeAs<clang::NamedDecl>("decl_name1"))
                        {
                            decl_name1 = decl_name_node1;
                            var_name1 = var_assign_node;
                            ifMatcher1_flag = 1;
                        }
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
                        if(const NamedDecl *decl_name_node3 = Result.Nodes.getNodeAs<clang::NamedDecl>("decl_name2"))
                        {
                            decl_name2 = decl_name_node3;
                            var_name2 = var_use_node;
                            useMatcher1_flag = 1;
                        }
                    }
                }
            }
            if(ifMatcher1_flag == 1 && useMatcher1_flag == 1 && if_end_line1 < use_start_line1 && areSameVariable(decl_name1, decl_name2))
            {
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << if_end_line1 << "," << use_start_line1 << "\n";
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

    Finder.addMatcher(ifMatcher, &Printer);
    Finder.addMatcher(useMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
