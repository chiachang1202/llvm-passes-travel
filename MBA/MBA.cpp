#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct MBA : public FunctionPass {
    static char ID;
    MBA() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      outs() << "Hello: ";
      outs().write_escaped(F.getName()) << '\n';
      return false;
    }
  };
}

char MBA::ID = 0;
static RegisterPass<MBA>
    X("mba",  // the option name -> -mba
      "Mixed Boolean Arithmetic Substitution", // option description
      true, // true as we don't modify the CFG
      false // true if we're writing an analysis
      );