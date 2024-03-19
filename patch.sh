echo "------------"
echo "Copy Code"
echo "------------"

# sudo cp -r $GITHUB_WORKSPACE/FunctionCount $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms
# ls -al $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/Timer

# sudo cp -r $GITHUB_WORKSPACE/Timer $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms
# ls -al $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/Timer

# sudo rm $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/CMakeLists.txt
# sudo cp $GITHUB_WORKSPACE/CMakeLists.txt $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/CMakeLists.txt


# .cpp .h
sudo cp -r $GITHUB_WORKSPACE/CodeCovPass $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms
sudo cp $GITHUB_WORKSPACE/KingsoftPass.h $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/include/llvm/Transforms/KingsoftPass.h

sudo rm $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/CMakeLists.txt
sudo cp $GITHUB_WORKSPACE/Transforms-CMakeLists.txt $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/Transforms/CMakeLists.txt

# addPass
sudo rm $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/CodeGen/TargetPassConfig.cpp
sudo cp $GITHUB_WORKSPACE/TargetPassConfig.cpp $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/CodeGen/TargetPassConfig.cpp
sudo rm $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/CodeGen/CMakeLists.txt
sudo cp $GITHUB_WORKSPACE/LLVMCodeGen-CMakeLists.txt $GITHUB_WORKSPACE/llvm-toolchain/toolchain/llvm-project/llvm/lib/CodeGen/CMakeLists.txt