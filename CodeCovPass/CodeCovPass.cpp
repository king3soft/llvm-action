#include "llvm/Transforms/KingsoftPass.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DebugInfoMetadata.h"

#include <fstream>

using namespace llvm;

namespace
{
    struct CodeCovPass : public FunctionPass
    {
        std::ofstream output;
        const char* codeCovPassEnv;
        const char* codeCovPassLog;

        static char ID;
        CodeCovPass() : FunctionPass(ID) {
            // 尝试获取环境变量
            codeCovPassEnv = std::getenv("CodeCovPassEnv");
            codeCovPassLog = std::getenv("CodeCovPassLog");
            if (codeCovPassLog) {
                const char* filepath = "D:\\CodeCovPass.log";
                output.open(filepath, std::ios::out | std::ios::app);
            }
            else 
            {
                output.open("./CodeCovPass.log", std::ios::out | std::ios::app);
            }

            if (codeCovPassEnv) {
                output << "CodeCovPassEnv: " << codeCovPassEnv << "\n" << std::endl;
            }
            else
            {
                output << "CodeCovPassEnv environment variable is not set.\n" << std::endl;
            }
        }

        virtual bool runOnFunction(Function &F) override {
            if (!codeCovPassEnv) {
                return false;
            }

            std::string FileName(codeCovPassEnv);

            if (auto *SP = F.getSubprogram()) {
                StringRef CurrentFileName = SP->getFilename();
                if (CurrentFileName.endswith(FileName)) {

                    output << "Function found: " << F.getName() << '\n' << std::endl;
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
