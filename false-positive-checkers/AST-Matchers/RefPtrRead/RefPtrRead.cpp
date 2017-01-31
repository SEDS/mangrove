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

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;


string File_Name;
int enter_bit = 1;
int decl_start_line = 0;
int use_start_line = 0;
int decl_flag = 0;
int use_flag = 0;
const NamedDecl *var_decl;
const NamedDecl *var_use;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST matcher to find a variable declaration that has the type char *&
StatementMatcher refDeclMatcher = declStmt(has(varDecl(hasType(asString("char *&"))).bind("var_decl"))).bind("ref_decl");

// AST matcher to find a function call that has the previously declared variable as an argument with an array subscriptor
StatementMatcher refUseMatcher = callExpr(hasAnyArgument(implicitCastExpr(hasDescendant(arraySubscriptExpr(hasDescendant(declRefExpr(to(varDecl().bind("var_use"))))))))).bind("ref_use");

class PatternFinder : public MatchFinder::MatchCallback
{
    public :
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            // Isolating the declaration statement
            if(const Stmt *ref_decl_node = Result.Nodes.getNodeAs<clang::Stmt>("ref_decl"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(ref_decl_node->getLocStart()))
                {
                    if(const NamedDecl *var_decl_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_decl"))
                    {
                        var_decl = var_decl_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(ref_decl_node->getLocEnd());
                        decl_start_line = FullLocation1.getSpellingLineNumber();
                        decl_flag = 1;
                    }
                }
            }

            // Isolating the use statement
            if(const Stmt *ref_use_node = Result.Nodes.getNodeAs<clang::Stmt>("ref_use"))
            {
                if(Result.Context->getSourceManager().isWrittenInMainFile(ref_use_node->getLocStart()))
                {
                    if(const NamedDecl *var_use_node = Result.Nodes.getNodeAs<clang::NamedDecl>("var_use"))
                    {
                        var_use = var_use_node;
                        FullSourceLoc FullLocation1 = Result.Context->getFullLoc(ref_use_node->getLocEnd());
                        use_start_line = FullLocation1.getSpellingLineNumber();
                        use_flag = 1;
                    }
                }
            }
            if(enter_bit == 1 && decl_flag == 1 && use_flag == 1 && decl_start_line < use_start_line && areSameVariable(var_decl, var_use))
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
    Finder.addMatcher(refDeclMatcher, &Printer);
    Finder.addMatcher(refUseMatcher, &Printer);
    return Tool.run(newFrontendActionFactory(&Finder).get());
}
