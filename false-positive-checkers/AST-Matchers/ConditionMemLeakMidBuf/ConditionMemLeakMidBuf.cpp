// Condition-Mem-Leak-Mid-Buf pattern checker
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

// Name of this false positive checker.
#define CHECKER_NAME "ConditionMemLeakMidBuf"

using namespace clang::ast_matchers;
using namespace std;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang;

string File_Name;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// AST Matcher expressions to match the FP pattern
StatementMatcher IfMatcher = ifStmt(allOf(
                                // Check that the IF condition contains a global variable expression.
                                anyOf(
                                    hasCondition(ignoringParenImpCasts(
                                        declRefExpr(to(varDecl(
                                            anyOf(
                                                (
                                                    hasGlobalStorage(),
                                                    hasInitializer(integerLiteral(unless(equals(0))))
                                                ),
                                                (
                                                    hasGlobalStorage(),
                                                    hasExternalFormalLinkage()
                                                )
                                            )
                                        )))
                                    )),
                                    hasCondition(binaryOperator(
                                        has(ignoringParenImpCasts(
                                            declRefExpr(to(varDecl(
                                                anyOf(
                                                    (
                                                        hasGlobalStorage(),
                                                        hasInitializer(integerLiteral(unless(equals(0))))
                                                    ),
                                                    (
                                                        hasGlobalStorage(),
                                                        hasExternalFormalLinkage()
                                                    )
                                                )
                                            )))
                                        ))
                                    ))
                                ),
                                // Check that the IF body has a memory free or delete.
                                hasDescendant(compoundStmt(
                                    anyOf(
                                        hasDescendant(callExpr(
                                            hasAnyArgument(ignoringParenImpCasts(
                                                declRefExpr().bind("var_free")
                                            )),
                                            hasDescendant(declRefExpr(
                                                to(functionDecl(hasName("free")))
                                            ))
                                        )),
                                        hasDescendant(cxxDeleteExpr())
                                    )
                                )),
                                // Check that the IF statement body modifies the pointer variable 
                                // (the invoked code ensures this variable is the one that is freed).
                                forEachDescendant(unaryOperator(
                                    hasOperatorName("++"),
                                    hasDescendant(
                                        declRefExpr().bind("var_modified")
                                    )
                                ))
                                
                            )).bind("ifStmt");



// Callback for the AST matchers
class PatternFinder : public MatchFinder::MatchCallback {
    public :
        virtual void run(const MatchFinder::MatchResult &Result) {
            Context = Result.Context;

            // Isolate the node identified by the AST matcher named 'IfMatcher'
            const Stmt *ifStmt = Result.Nodes.getNodeAs<clang::Stmt>("ifStmt");
            const DeclRefExpr *varFree = Result.Nodes.getNodeAs<clang::DeclRefExpr>("var_free");
            const DeclRefExpr *varModified = Result.Nodes.getNodeAs<clang::DeclRefExpr>("var_modified");
            
            // Verify that the two variables are the same and the modification happens BEFORE the free.
            if (areSameVariable(varModified, varFree) && happensBefore(varModified, varFree)) {
                // Get line number of the end of scope for the IF statement's parent.
                unsigned int scopeEndLine = 0;
                auto it = Context->getParents(*ifStmt).begin();
                if (it != Context->getParents(*ifStmt).end()) {
                    const clang::Stmt *parentStmt = it->get<clang::Stmt>();
                    scopeEndLine = Context->getSourceManager().getPresumedLineNumber(parentStmt->getLocEnd());
                }

                // Print the end of scope line number.
                errs() << "False positive detected:" << CHECKER_NAME << ":" << File_Name << ":" << scopeEndLine << " (end of scope)\n";
            }
        }
        
    private:
        ASTContext *Context;
        
        // Check that the given two declarations are the same.
        bool areSameVariable(const DeclRefExpr *first, const DeclRefExpr *second) {
            return first && second && first->getDecl()->getCanonicalDecl() == second->getDecl()->getCanonicalDecl();
        }
        
        // Check that the first declaration appears before the second one in the source code. 
        bool happensBefore(const DeclRefExpr *first, const DeclRefExpr *second) {
            unsigned int firstLine = Context->getSourceManager().getPresumedLineNumber(first->getLocStart());
            unsigned int secondLine = Context->getSourceManager().getPresumedLineNumber(second->getLocStart());
            return firstLine < secondLine;
        }
};

int main(int argc, const char **argv) {
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    File_Name = argv[1];
    PatternFinder PatFinder;
    MatchFinder Finder;

    // Add the AST matcher expression to the match callback
    Finder.addMatcher(IfMatcher, &PatFinder);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
