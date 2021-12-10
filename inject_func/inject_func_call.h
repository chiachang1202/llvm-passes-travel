#ifndef INJECT_FUNC_CALL_H
#define INJECT_FUNC_CALL_H

#include "llvm/Pass.h" 
#include "llvm/IR/PassManager.h"

//------------------------------------------------------------------------------
// Legacy PM interface
//------------------------------------------------------------------------------
struct InjectFuncCall : public llvm::ModulePass {
  static char ID;
  InjectFuncCall() : llvm::ModulePass(ID) {}
  bool runOnModule(llvm::Module &M) override;
};

#endif