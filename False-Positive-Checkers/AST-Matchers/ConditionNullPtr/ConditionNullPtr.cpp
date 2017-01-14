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

std::string File_Name;
int enter_bit = 1;
int if_end_line1 = 0;
int if_end_line2 = 0;
int use_start_line1 = 0;
int ifMatcher1_flag = 0;
int ifMatcher2_flag = 0;
int useMatcher1_flag = 0;
const NamedDecl *var_name1;
const NamedDecl *var_name2;
const NamedDecl *var_name3;
const NamedDecl *decl_name1;
const NamedDecl *decl_name2;
const NamedDecl *decl_name3;


static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find an 'if' statement with a memory allocation to a variable
StatementMatcher ifMatcher1 = ifStmt( hasCondition(has(declRefExpr(to(varDecl(hasGlobalStorage(), hasType(isConstQualified())).bind("cond_var"))))),
                                      hasDescendant(compoundStmt(hasDescendant(binaryOperator( hasLHS(declRefExpr(to(varDecl().bind("var_assign")))),
                                                                                               hasRHS(cStyleCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl(hasName("__builtin_alloca"))))))))) )))), hasAncestor(functionDecl().bind("decl_name1")) ).bind("if_stmt1");

// AST matcher to find an 'if' statement with a variable initialization
StatementMatcher ifMatcher2 = ifStmt( hasDescendant(compoundStmt(hasDescendant(binaryOperator( hasDescendant(declRefExpr(to(varDecl(hasInitializer(anything())).bind("var_init")))) )))), hasAncestor(functionDecl().bind("decl_name2")) ).bind("if_stmt2");

// AST matcher to find the variable being used in the statement data[0] = 5
StatementMatcher useMatcher1 = binaryOperator( hasLHS(arraySubscriptExpr( hasDescendant(declRefExpr(to(varDecl().bind("var_use")))), has(integerLiteral(equals(0))) )),
                                               hasRHS(integerLiteral()),
                                               hasAncestor(functionDecl().bind("decl_name3")) ).bind("use_stmt");


class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Stmt *if_stmt_node1 = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt1"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt_node1->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt_node1->getLocEnd());
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
            else if(const Stmt *if_stmt_node2 = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt2"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt_node2->getLocStart()))
                {
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt_node2->getLocEnd());
                    if_end_line2 = FullLocation1.getSpellingLineNumber();
                    if(const NamedDecl *var_init_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_init"))
                    {
                        if(const NamedDecl *decl_name_node2 = Result.Nodes.getNodeAs<clang::NamedDecl>("decl_name2"))
                        {
                            decl_name2 = decl_name_node2;
                            var_name2 = var_init_node;
                            ifMatcher2_flag = 1;
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
                        if(const NamedDecl *decl_name_node3 = Result.Nodes.getNodeAs<clang::NamedDecl>("decl_name3"))
                        {
                            decl_name3 = decl_name_node3;
                            var_name3 = var_use_node;
                            useMatcher1_flag = 1;
                        }
                    }
                }
            }
            // Checking if the use statement is written after the 'if' statement, the enter_bit is set and the matchers have matched the expression
            if(if_end_line1 < use_start_line1 && enter_bit == 1 && ifMatcher1_flag == 1 && useMatcher1_flag == 1 && areSameVariable(decl_name1, decl_name3))
            {
                errs() << "\n" << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                // Resetting the enter_bit in order to exit the program after the first instance of the pattern has been identified
                enter_bit = 0;
            }
            // Checking if the use statement is written after the 'if' statement, the enter_bit is set and the matchers have matched the expression
            else if(if_end_line2 < use_start_line1 && enter_bit == 1 && ifMatcher2_flag == 1 && useMatcher1_flag == 1 && areSameVariable(decl_name2, decl_name3))
            {
                errs() << "\n" << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                // Resetting the enter_bit in order to exit the program after the first instance of the pattern has been identified
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
    Finder.addMatcher(ifMatcher1, &Printer);
    Finder.addMatcher(ifMatcher2, &Printer);
    Finder.addMatcher(useMatcher1, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
