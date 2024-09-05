#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{

    struct CheckpointPass : public FunctionPass
    {
        static char ID;
        CheckpointPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override
        {
            bool modified = false;
            static int BasicBlockID = 0;

            for (BasicBlock &BB : F)
            {
                Instruction *insertPoint = nullptr;
                for (Instruction &Inst : BB)
                {
                    if (isa<ReturnInst>(&Inst))
                    {
                        insertPoint = &Inst;
                        break;
                    }
                }

                if (!insertPoint)
                    continue;

                IRBuilder<> builder(insertPoint);
                builder.SetInsertPoint(&BB, insertPoint->getIterator());

                FunctionCallee checkpointFunc = F.getParent()->getOrInsertFunction(
                    "perform_checkpoint",
                    Type::getVoidTy(F.getContext()),
                    Type::getInt8PtrTy(F.getContext()),
                    Type::getInt32Ty(F.getContext()));

                // Pass the function name and basic block ID as arguments to perform_checkpoint
                Value *funcName = builder.CreateGlobalStringPtr(F.getName());
                Value *blockID = builder.getInt32(BasicBlockID);
                builder.CreateCall(checkpointFunc, {funcName, blockID});
                errs() << "Checkpoint after Basic Block: " << BasicBlockID << " in function: " << F.getName().str() << "\n";
                modified = true;
                BasicBlockID++;
            }

            return modified;
        }
    };

} // end anonymous namespace

char CheckpointPass::ID = 0;
static RegisterPass<CheckpointPass> X("insert-checkpoint", "Insert Checkpoints After Each Function");