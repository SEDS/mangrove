// Ref-Ptr-Read pattern checker
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




static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find a function declaration that contains a pointer reference but no dereference
DeclarationMatcher refPtrMatcher = functionDecl( hasDescendant(varDecl(hasType(asString("char *&"))).bind("var_decl")), hasDescendant(declRefExpr( to(varDecl(equalsBoundNode("var_decl")).bind("var_use")), unless(hasParent(implicitCastExpr(hasParent(unaryOperator(hasOperatorName("*")))))) )) ).bind("ref_ptr");

std::string File_Name;

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            if(const Decl *ref_ptr_node = Result.Nodes.getNodeAs<clang::Decl>("ref_ptr"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(ref_ptr_node->getLocStart()))
                {
                    errs() << File_Name;
                    errs() << "\n" << "FP Located" << "\n";
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
    Finder.addMatcher(refPtrMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
