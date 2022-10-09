#include "llvm/ADT/Statistic.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {
  struct MBA : public FunctionPass {
    static char ID;
    MBA() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) {
      bool changed = false;
      // outs() << "Basic block (name=" << BB.getName() << ") has " << BB.size() << " instructions.\n";
      for (auto &BB : F) {
        // for (auto &Ins : BB) {
        //   auto *BinOp = dyn_cast<BinaryOperator>(&Ins);

        //   // We only accept the sub arithmetic operation.
        //   if (!BinOp) {
        //     continue;
        //   }
        //   // The modification
        //   // (a - b) --> (a + ~b) + 1
        //   // can only apply to integer substitution
        //   unsigned Opcode = BinOp->getOpcode();
        //   if (Opcode != Instruction::Sub || !BinOp->getType()->isIntegerTy()) {
        //     continue;
        //   }

        //   IRBuilder<> Builder(BinOp);

        //   Instruction *NewValue = BinaryOperator::CreateAdd(
        //     Builder.CreateAdd(BinOp->getOperand(0),
        //                       Builder.CreateNot(BinOp->getOperand(1))),
        //     ConstantInt::get(BinOp->getType(), 1));

        //   outs() << "Replace " << *BinOp << " to " << *NewValue << "\n";

        //   BasicBlock::iterator BI(BinOp);
        //   ReplaceInstWithInst(BinOp->getParent()->getInstList(), BI, NewValue);
        //   // ReplaceInstWithInst(NewValue, BinOp);

        //   changed |= true;
        // }

        for (auto Inst = BB.begin(), IE = BB.end(); Inst != IE; ++Inst) {
          // Skip non-binary (e.g. unary or compare) instruction.
          auto *BinOp = dyn_cast<BinaryOperator>(Inst);
          if (!BinOp)
            continue;

          /// Skip instructions other than integer sub.
          unsigned Opcode = BinOp->getOpcode();
          if (Opcode != Instruction::Sub || !BinOp->getType()->isIntegerTy())
            continue;

          // A uniform API for creating instructions and inserting
          // them into basic blocks.
          IRBuilder<> Builder(BinOp);

          // Create an instruction representing (a + ~b) + 1
          Instruction *NewValue = BinaryOperator::CreateAdd(
              Builder.CreateAdd(BinOp->getOperand(0),
                                Builder.CreateNot(BinOp->getOperand(1))),
              ConstantInt::get(BinOp->getType(), 1));

          // The following is visible only if you pass -debug on the command line
          // *and* you have an assert build.
          // LLVM_DEBUG(dbgs() << *BinOp << " -> " << *NewValue << "\n");

          // Replace `(a - b)` (original instructions) with `(a + ~b) + 1`
          // (the new instruction)
          outs() << "Replace " << *BinOp << " to " << *NewValue << "\n";
          ReplaceInstWithInst(BB.getInstList(), Inst, NewValue);
          // ReplaceInstWithInst(dyn_cast<Instruction>(BinOp), NewValue);
          changed |= true;
        }
      }
      return changed;
    }
  };
}

char MBA::ID = 0;
static RegisterPass<MBA>
    X("mba",  // the option name -> -mba
      "MBA Sub", // option description
      true, // true as we don't modify the CFG
      false // true if we're writing an analysis
      );