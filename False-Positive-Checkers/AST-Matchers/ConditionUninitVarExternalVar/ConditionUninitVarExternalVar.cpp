// Condition-Uninit-Var-External-Var pattern checker
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
int enter_bit = 1;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find a function declaration that contains a variable being initialized a reference in an 'if' body and used outside the 'if' body
DeclarationMatcher functionMatcher = functionDecl( has(compoundStmt( hasDescendant(ifStmt( hasCondition(implicitCastExpr(has(declRefExpr(to(varDecl( hasGlobalStorage(), hasType(isConstQualified()) ).bind("cond_var")))))),                                          has(compoundStmt(hasDescendant(binaryOperator( hasOperatorName("="),
                                                                                                           hasLHS(declRefExpr(to(varDecl().bind("lhs_var")))),
                                                                                                           hasRHS(unaryOperator( hasOperatorName("&"),
                                                                                                                                 has(declRefExpr(to(varDecl().bind("rhs_var")))) )) )))) )),                                              hasDescendant(callExpr( hasAnyArgument(unaryOperator( hasOperatorName("*"),
                                                                                                     has(declRefExpr(to(varDecl(equalsBoundNode("lhs_var")).bind("var_use")))) )) )) )) ).bind("func_matcher");



class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Decl *func_matcher_node = Result.Nodes.getNodeAs<clang::Decl>("func_matcher"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(func_matcher_node->getLocStart()))
                {
                    // Checking if the first instance of the FP pattern has been found in the source file
                    if(enter_bit == 1)
                    {
                        errs() << "\n" << File_Name;
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
    Finder.addMatcher(functionMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
