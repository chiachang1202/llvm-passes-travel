#ifndef LOOP_TAILING_H
#define LOOP_TAILING_H

#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/PassManager.h"

//------------------------------------------------------------------------------
// Legacy PM interface
//------------------------------------------------------------------------------
struct Hello : public llvm::LoopPass {
  static char ID;
  Hello() : llvm::LoopPass(ID) {}
  bool runOnLoop(llvm::Loop *L, llvm::LPPassManager &LPM) override;
};

#endif