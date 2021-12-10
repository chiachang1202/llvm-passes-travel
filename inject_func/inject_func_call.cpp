#include "inject_func_call.h"
#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace {
  //declare a “Hello” class that is a subclass of ModulePass. 
  struct InjectFuncCall : public ModulePass {
    //pass identifier used by LLVM to identify pass
    static char ID;
    InjectFuncCall() : ModulePass(ID) {}
    //override an abstract virtual method inherited from FunctionPass. 
    virtual bool runOnModule(Module &M) {

      
      
      for (Function &F : M) {

        errs() << "Hello " <<  F.getName() << "\n";
        if (F.isDeclaration()) {
          errs() << "Function " <<  F.getName() << " is declaration." << "\n";
        }

      }

      return true;
    }
  };

  char InjectFuncCall::ID = 0;

  //register class 
  static RegisterPass<InjectFuncCall> X("inject-func-call", "Inject `Printf` function call", false, false);
  
}