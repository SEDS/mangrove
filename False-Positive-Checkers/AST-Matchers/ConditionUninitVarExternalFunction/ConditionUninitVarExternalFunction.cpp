// Condition-Uninit-Var-External-Function pattern checker
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
int if_end_line = 0;
int use_start_line = 0;
int if_flag1 = 0;
int if_flag2 = 0;
int if_flag3 = 0;
int use_flag = 0;
const Stmt *if_stmt1_node_var;
const Stmt *if_stmt2_node_var;
const Stmt *if_stmt3_node_var;
const NamedDecl *lhs_var;
const NamedDecl *lhs_var3;
const NamedDecl *lhs_var_use;
const NamedDecl *member_var_decl;
const NamedDecl *member_var_use_decl;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher for an 'if' statement with a function in the condition and variable being initialized using 'new' operator in the body
StatementMatcher ifMatcher1 = ifStmt(hasCondition(implicitCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl()))))))),
                                     has(compoundStmt( hasDescendant(binaryOperator( hasLHS(declRefExpr(to(varDecl().bind("lhs_var")))),
                                                                                     hasRHS(cxxNewExpr()) )) ))).bind("if_stmt1");

// AST matcher for an 'if' statement with a function in the condition and the member variable being assigned a value
StatementMatcher ifMatcher2 = ifStmt(hasCondition(implicitCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl()))))))),
                                     has(compoundStmt( hasDescendant(binaryOperator( hasLHS(memberExpr().bind("mem_var")) )) ))).bind("if_stmt2");

// AST matcher for an 'if' statement with a function in the condition and a variable being assigned another variable
StatementMatcher ifMatcher3 = ifStmt(hasCondition(implicitCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl()))))))),
                                     has(compoundStmt( hasDescendant(binaryOperator( hasLHS(declRefExpr(to(varDecl().bind("lhs_var3")))),
                                                                                     hasRHS(implicitCastExpr(has(declRefExpr(to(varDecl().bind("rhs_var")))))) )) ))).bind("if_stmt3");

// AST matcher for a function using the member variable as an argument
StatementMatcher callMatcher = callExpr(hasAnyArgument(implicitCastExpr(has(memberExpr(hasDescendant(declRefExpr(to(varDecl().bind("lhs_var_use"))))).bind("mem_var_use"))))).bind("call_stmt");


class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            Context = Result.Context;

            // Isolating the 'if' statement according to ifMatcher1
            if(const Stmt *if_stmt1_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt1"))
            {
                if_stmt1_node_var = if_stmt1_node;
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt1_node->getLocStart()))
                {
                    if(const NamedDecl *lhs_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var"))
                    {
                        lhs_var = lhs_var_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt1_node->getLocEnd());
                        if_end_line = FullLocation1.getSpellingLineNumber();
                        if_flag1 = 1;
                    }

                }
            }
            // Isolating the 'if' statement according to ifMatcher2
            if(const Stmt *if_stmt2_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt2"))
            {
                if_stmt2_node_var = if_stmt2_node;
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt2_node->getLocStart()))
                {
                    if(const MemberExpr *mem_var_node = Result.Nodes.getNodeAs<clang::MemberExpr>("mem_var"))
                    {
                        ValueDecl *mem_var_value = mem_var_node->getMemberDecl();
                        if(const NamedDecl *mem_var_decl = dyn_cast<NamedDecl>(mem_var_value))
                        {
                            member_var_decl = mem_var_decl;
                            if_flag2 = 1;
                        }
                    }

                }
            }
            // Isolating the 'if' statement according to ifMatcher3
            if(const Stmt *if_stmt3_node = Result.Nodes.getNodeAs<clang::Stmt>("if_stmt3"))
            {
                if_stmt3_node_var = if_stmt3_node;
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_stmt3_node->getLocStart()))
                {
                    if(const NamedDecl *lhs_var3_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var3"))
                    {
                        lhs_var3 = lhs_var3_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_stmt3_node->getLocEnd());
                        if_end_line = FullLocation1.getSpellingLineNumber();
                        if_flag3 = 1;
                    }

                }
            }
            // Isolating the use statement according to callMatcher
            if(const Stmt *call_stmt_node = Result.Nodes.getNodeAs<clang::Stmt>("call_stmt"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(call_stmt_node->getLocStart()))
                {
                    if(const NamedDecl *lhs_var_use_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var_use"))
                    {
                        lhs_var_use = lhs_var_use_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(call_stmt_node->getLocStart());
                        use_start_line = FullLocation1.getSpellingLineNumber();
                    }
                    if(const MemberExpr *mem_var_use_node = Result.Nodes.getNodeAs<clang::MemberExpr>("mem_var_use"))
                    {
                        ValueDecl *mem_var_use_value = mem_var_use_node->getMemberDecl();
                        if(const NamedDecl *mem_var_use_decl = dyn_cast<NamedDecl>(mem_var_use_value))
                        {
                            member_var_use_decl = mem_var_use_decl;
                            use_flag = 1;
                        }
                    }

                }
            }
            // Reporting the presence of the FP when the 'if' statement is matcher by matchers ifMatcher1, ifMatcher2 and callMatcher
            if(enter_bit == 1 && if_flag1 == 1 && if_flag2 == 1 && use_flag == 1 && if_end_line < use_start_line && areSameVariable(lhs_var, lhs_var_use) && areSameVariable(member_var_decl, member_var_use_decl) && areSameExpr(Context, if_stmt1_node_var, if_stmt2_node_var))
            {
                errs() << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                enter_bit = 0;
            }
            // Reporting the presence of the FP when the 'if' statement is matched by matchers ifMatcher2, ifMatcher3 and callMatcher
            else if(enter_bit == 1 && if_flag2 == 1 && if_flag3 == 1 && use_flag == 1 && if_end_line < use_start_line && areSameVariable(lhs_var3, lhs_var_use) && areSameVariable(member_var_decl, member_var_use_decl) && areSameExpr(Context, if_stmt2_node_var, if_stmt3_node_var))
            {
                errs() << File_Name;
                errs() << "\n" << "FP Located" << "\n";
                enter_bit = 0;
            }
        }

        // Function to check if the two variable nodes are the same
        static bool areSameVariable(const NamedDecl *First, const NamedDecl *Second)
        {
            return First && Second && First->getCanonicalDecl() == Second->getCanonicalDecl();
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
    PatternFinder Printer;
    MatchFinder Finder;

    Finder.addMatcher(ifMatcher1, &Printer);
    Finder.addMatcher(ifMatcher2, &Printer);
    Finder.addMatcher(ifMatcher3, &Printer);
    Finder.addMatcher(callMatcher, &Printer);
    
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
