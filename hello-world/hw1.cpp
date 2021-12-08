#include "llvm/Pass.h" 
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
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
      errs() << "Module: " << "\n";
      errs() << "Hello: ";
      errs() << M.getName() << '\n';

      errs() << "Function: " << "\n";
      for (Function &F : M) {
        errs() << "Hello: ";
        errs() << F.getName() << '\n';
      }

      return true;
    }
  };
}

char Hello::ID = 0;

//register class 
static RegisterPass<Hello> X("hello", "Hello World Pass");