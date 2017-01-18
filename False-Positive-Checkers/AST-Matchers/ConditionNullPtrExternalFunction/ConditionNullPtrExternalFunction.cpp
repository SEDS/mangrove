// Condition-Null-Ptr-External-Function pattern checker
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
int call_start_line = 0;
int if_flag = 0;
int call_flag = 0;
const NamedDecl *lhs_var;
const NamedDecl *assign_lhs;
const NamedDecl *use_var;




static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to identify 'if' statement that contains a memory allocation using 'malloc' and variable initialization
StatementMatcher ifMatcher = ifStmt( hasCondition(callExpr(hasDescendant(declRefExpr(to(functionDecl()))))),
                                     has(compoundStmt( hasDescendant(binaryOperator( hasOperatorName("="),
                                                                                     hasLHS(declRefExpr(to(varDecl().bind("lhs_var")))),
                                                                                     hasRHS(cStyleCastExpr(has(callExpr(hasDescendant(declRefExpr(to(functionDecl(hasName("malloc"))))))))) )),
                                                       hasDescendant(binaryOperator( hasOperatorName("="),
                                                                                     hasLHS(unaryOperator(hasOperatorName("*"), hasDescendant(declRefExpr(to(varDecl().bind("assign_lhs")))))) )) )) ).bind("if_matcher");

// AST matcher to identify function call using the previously initialized variable
StatementMatcher funcCallMatcher = callExpr(hasAnyArgument(implicitCastExpr(has(unaryOperator( hasOperatorName("*"),
                                                                                               hasDescendant(declRefExpr(to(varDecl().bind("use_var")))) ))))).bind("func_call_matcher");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            // Isolating the 'if' statement
            if(const Stmt *if_matcher_node = Result.Nodes.getNodeAs<clang::Stmt>("if_matcher"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(if_matcher_node->getLocStart()))
                {
                    if(const NamedDecl *lhs_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("lhs_var"))
                    {
                        lhs_var = lhs_var_node;
                    }
                    if(const NamedDecl *assign_lhs_node = Result.Nodes.getNodeAs<clang::NamedDecl>("assign_lhs"))
                    {
                        assign_lhs = assign_lhs_node;
                    }
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(if_matcher_node->getLocEnd());
                    if_end_line = FullLocation1.getSpellingLineNumber();
                    if_flag = 1;

                }
            }
            // Isolating the function call
            if(const Stmt *func_call_matcher_node = Result.Nodes.getNodeAs<clang::Stmt>("func_call_matcher"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(func_call_matcher_node->getLocStart()))
                {
                    if(const NamedDecl *use_var_node = Result.Nodes.getNodeAs<clang::NamedDecl>("use_var"))
                    {
                        use_var = use_var_node;
                    }
                    FullSourceLoc FullLocation1 = Result.Context->getFullLoc(func_call_matcher_node->getLocStart());
                    call_start_line = FullLocation1.getSpellingLineNumber();
                    call_flag = 1;

                }
            }
            // Flagging the presence of FP if the variables are same and the location of the function call is after the 'if' body
            if(if_flag == 1 && call_flag == 1 && enter_bit == 1 && areSameVariable(lhs_var, assign_lhs) && areSameVariable(assign_lhs, use_var) && if_end_line < call_start_line)
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
    Finder.addMatcher(ifMatcher, &Printer);
    Finder.addMatcher(funcCallMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
