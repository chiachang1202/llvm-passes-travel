#include "LoopTailing.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace {
  //declare a “Hello” class that is a subclass of ModulePass. 
  struct Hello : public LoopPass {
    //pass identifier used by LLVM to identify pass
    static char ID;
    Hello() : LoopPass(ID) {}
    //override an abstract virtual method inherited from FunctionPass. 

    virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override
    {
      
      // outs() << "Loop Header Block:" << "\n";
      BasicBlock *LH = L->getHeader();
      for (BasicBlock::iterator LHI = LH->begin(); LHI != LH->end(); ++LHI) {
        if (dyn_cast<ICmpInst>(LHI)) {
          // outs() << *LHI << "\n";
          Value *old_operand = LHI->getOperand(1);
          Value *new_operand = ConstantInt::get(old_operand->getType(), 220);
          
          LHI->getOperand(1)->replaceAllUsesWith(new_operand);
        }
      }

      // outs() << "Loop Exit Block:" << "\n";
      // BasicBlock *LE = L->getLoopLatch();
      // for (BasicBlock::iterator LEI = LE->begin(); LEI != LE->end(); ++LEI) {
      //   outs() << *LEI << "\n";
      // }

      return true;
    }
  };

  char Hello::ID = 0;

  //register class 
  static RegisterPass<Hello> X("hello", "Loop Tailing Pass", false, false);
  
}