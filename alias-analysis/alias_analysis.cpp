#include "alias_analysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  //declare a “Hello” class that is a subclass of ModulePass. 
  struct Hello : public ModulePass {
    //pass identifier used by LLVM to identify pass
    static char ID;
    Hello() : ModulePass(ID) {}
    //override an abstract virtual method inherited from FunctionPass. 
    virtual bool runOnModule(Module &M) {
      
      for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (Function::iterator BB = F->begin(); BB != F->end(); BB++) {
          for (BasicBlock::iterator Ins = BB->begin(); Ins != BB->end(); Ins++) {
            if (dyn_cast<AllocaInst>(Ins)) {
              errs() << *Ins << "\n";
              Type *ty = Ins->getType();
              if (ty->isPointerTy()) {
                Type *ptty = dyn_cast<PointerType>(ty)->getElementType();
                errs() << *ptty << "\n";
              }
            }
            // if (dyn_cast<LoadInst>(Ins)) {
            //   errs() << "load" << "\n";
            //   Type *ty = Ins->getType();
            //   if (ty->isPointerTy()) {
            //     Type *ptty = dyn_cast<PointerType>(ty)->getElementType();
            //     errs() << *Ins << " [" << *ptty << "]" << "\n";
            //   }
            //   Value *val0 = Ins->getOperand(0);
            //   Type *ty0 = val0->getType();
            //   if (ty0->isPointerTy()) {
            //     Type *ptty0 = dyn_cast<PointerType>(ty0)->getElementType();
            //     errs() << *val0 << " [" << *ptty0 << "]" << "\n";
            //   }
            //   if (ty0->isIntegerTy()) {
            //     errs() << *val0 << " [" << *ty0 << "]" << "\n";
            //   }
            //   errs() << "\n";
            // }
            // if (dyn_cast<StoreInst>(Ins)) {
            //   errs() << "store" << "\n";
            //   Value *val0 = Ins->getOperand(0);
            //   Type *ty0 = val0->getType();
            //   if (ty0->isPointerTy()) {
            //     Type *ptty0 = dyn_cast<PointerType>(ty0)->getElementType();
            //     errs() << *val0 << " [" << *ptty0 << "]" << "\n";
            //   }
            //   if (ty0->isIntegerTy()) {
            //     errs() << *val0 << " [" << *ty0 << "]" << "\n";
            //   }

            //   Value *val1 = Ins->getOperand(1);
            //   Type *ty1 = val1->getType();
            //   if (ty1->isPointerTy()) {
            //     Type *ptty1 = dyn_cast<PointerType>(ty1)->getElementType();
            //     errs() << *val1 << " [" << *ptty1 << "]" << "\n";
            //   }
            //   if (ty1->isIntegerTy()) {
            //     errs() << *val1 << " [" << *ty1 << "]" << "\n";
            //   }
            //   errs() << "\n";
            // }
          }
        }
      }

      return false;
    }
  };

  char Hello::ID = 0;

  //register class 
  static RegisterPass<Hello> X("hello", "Hello World Pass", false, false);
  
}