#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace
{
    struct FunctionCountPass : public FunctionPass
    {
        static char ID;
        FunctionCountPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F)
        {
            errs() << "Function found: " << F.getName() << '\n';
            return false;
        }
    };
}

char FunctionCountPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerFunctionCountPass(const PassManagerBuilder &,
                                   legacy::PassManagerBase &PM)
{
    PM.add(new FunctionCountPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerFunctionCountPass);