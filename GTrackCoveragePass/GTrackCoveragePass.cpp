#include "llvm/Transforms/KingsoftPass.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DebugInfoMetadata.h"

#include "toml.hpp"
#include <fstream>

using namespace llvm;

namespace
{
class GTrackCoveragePass : public FunctionPass
{

public:
    static char ID;
    GTrackCoveragePass() : FunctionPass(ID) {
        const char *confFile = std::getenv("GTrackCoverageConf");
        if (!confFile) {
            enable = false;
            errs() << "[GTrackCoveragePass] confFile is not found\n";
            return;
        }

        enable = initializeGTrackCoveragePass(confFile);
    }

    bool initializeGTrackCoveragePass(const char *confFile);
    bool isIngore(StringRef filename, StringRef functionName);
    bool runOnFunction(Function &F) override;

private:
    bool enable = false;
    std::vector<std::string> include_files;
    std::vector<std::string> ignore_functions;
};
}

bool GTrackCoveragePass::initializeGTrackCoveragePass(const char *confFile) {

    try {
        auto tbl = toml::parse(confFile);
        if (toml::find(tbl, "include", "files").is_array()) {
            auto arr = *toml::find(tbl, "include", "files").as_array();
            for (auto &&elem : arr) {
                include_files.push_back(elem.value_or(""));
            }
        }
        if (toml::find(tbl, "ignore", "functions").is_array()) {
            auto arr = *toml::find(tbl, "ignore", "functions").as_array();
            for (auto &&elem : arr) {
                ignore_functions.push_back(elem.value_or(""));
            }
        }
    } catch (const std::exception &e) {
        errs() << "[GTrackCoveragePass] conf parsing failed: " << e.what() << '\n';
        return false;
    }

    return true;
}

bool GTrackCoveragePass::isIngore(StringRef filename, StringRef functionName) {
    auto it = std::find_if(
        include_files.begin(), include_files.end(),
        [filename](std::string &x) { return filename.endswith(x); });
    if (it == include_files.end()) return false;

    auto it2 = std::find_if(
        ignore_functions.begin(), ignore_functions.end(),
        [functionName](std::string &x) { return functionName.contains(x); });
    if (it != ignore_functions.end()) return false;

    return true;
}

bool GTrackCoveragePass::runOnFunction(Function &F) {
    if (!enable) {
        return false;
    }

    if (auto *SP = F.getSubprogram()) {
        StringRef filename = SP->getFilename();
        StringRef functionName = F.getName();
        if (!isIngore(filename, functionName)) {
            LLVMContext &Context = F.getContext();
            Module *M = F.getParent();

            // void GTrack_Coverage(const char *)
            FunctionCallee logFunc = M->getOrInsertFunction("GTrack_Coverage",
                FunctionType::get(Type::getVoidTy(Context), {Type::getInt8PtrTy(Context)}, false));

            IRBuilder<> Builder(&*F.getEntryBlock().getFirstInsertionPt());
            
            // inlinable function call in a function with debug info must have a !dbg location
            auto *DILoc = DILocation::get(Context, SP->getLine(), 0, SP);
            Builder.SetCurrentDebugLocation(DILoc); 

            Value *funcName = Builder.CreateGlobalStringPtr(functionName);
            Builder.CreateCall(logFunc, {funcName});

            return true;
        }
    }
    return false;
}

char GTrackCoveragePass::ID = 0;

FunctionPass *llvm::createGTrackCoveragePass() {
  return new GTrackCoveragePass();
}
