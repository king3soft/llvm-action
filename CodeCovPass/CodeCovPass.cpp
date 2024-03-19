#include "llvm/Transforms/KingsoftPass.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/CommandLine.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/Triple.h"
#include "llvm/IR/CallingConv.h"

#include "llvm/IR/Instruction.h"
#include "llvm/InitializePasses.h"

#include <fstream>

using namespace llvm;

namespace
{
    struct CodeCovPass : public FunctionPass
    {
        std::ofstream output;
        static char ID;
        CodeCovPass() : FunctionPass(ID) {
            const char* filepath = "D:\\CodeCovPass.log";
            output.open(filepath, std::ios::out | std::ios::app);
        }

        virtual bool runOnFunction(Function &F) override {

            // 尝试获取环境变量
            const char* CodeCovPassEnv = std::getenv("CodeCovPassEnv");
            if (!CodeCovPassEnv) {
                output << "CodeCovPassEnv environment variable is not set.\n" << std::endl;
                errs() << "CodeCovPassEnv environment variable is not set.\n";
                return false;
            }
            std::string FileName(CodeCovPassEnv);

            if (auto *SP = F.getSubprogram()) {
                StringRef CurrentFileName = SP->getFilename();
                if (CurrentFileName.endswith(FileName)) {

                    // Context
                    LLVMContext &Context = F.getContext();
                    Module *M = F.getParent();

                    // 声明需要插入的函数 void LogCodeCov(const char *)
                    FunctionCallee logFunc = M->getOrInsertFunction("LogCodeCov",
                    FunctionType::get(Type::getVoidTy(Context), {Type::getInt8PtrTy(Context)}, false));


                    auto *DILoc = DILocation::get(Context, SP->getLine(), 0, SP);

                    // 构造参数 然后插入到函数开头进行调用
                    IRBuilder<> Builder(&*F.getEntryBlock().getFirstInsertionPt());
                    Value *funcName = Builder.CreateGlobalStringPtr(F.getName());
                    Builder.SetCurrentDebugLocation(DILoc); // inlinable function call in a function with debug info must have a !dbg location
                    Builder.CreateCall(logFunc, {funcName});

                    return true;

                } else {
                    output << "Function " << F.getName().data() << " is not defined in file hellovk.h\n" << std::endl;
                    errs() << "Function " << F.getName() << " is not defined in file hellovk.h\n";
                    return false; // 确保返回false，因为函数没有被修改
                }
            }
            return false;
        }
    };
}

char CodeCovPass::ID = 0;

FunctionPass *llvm::createCodeCovPass() {
  return new CodeCovPass();
}