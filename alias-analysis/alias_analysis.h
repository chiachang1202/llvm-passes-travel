#ifndef HW1_H
#define HW1_H

#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

//------------------------------------------------------------------------------
// Legacy PM interface
//------------------------------------------------------------------------------
struct Hello : public llvm::ModulePass {
  static char ID;
  Hello() : llvm::ModulePass(ID) {}
  bool runOnModule(llvm::Module &M) override;
};

#endif