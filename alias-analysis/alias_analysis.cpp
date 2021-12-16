#include "alias_analysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

#include <unordered_map>

using namespace llvm;

namespace {
  //declare a “Hello” class that is a subclass of ModulePass. 
  struct Hello : public ModulePass {
    //pass identifier used by LLVM to identify pass
    static char ID;
    Hello() : ModulePass(ID) {}

    // analysis used data structure
    std::unordered_map<Value*, std::string> variable;
    std::unordered_map<std::string, std::string> tdef = {};
    std::unordered_map<std::string, std::string> tequ = {};
    int nline = 0;

    //override an abstract virtual method inherited from FunctionPass. 
    virtual bool runOnModule(Module &M) {
      
      for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (Function::iterator BB = F->begin(); BB != F->end(); BB++) {
          for (BasicBlock::iterator Ins = BB->begin(); Ins != BB->end(); Ins++) {
            if (dyn_cast<AllocaInst>(Ins)) {
              // errs() << *Ins << "\n";
              Type *ty = Ins->getType();
              std::string name = Ins->getName().str();
              if (ty->isPointerTy()) {
                Type *ptty = dyn_cast<PointerType>(ty)->getElementType();
                variable[dyn_cast<Value>(Ins)] = name;
              }
            }

            if (dyn_cast<LoadInst>(Ins)) {

              // errs() << "load" << "\n";
              Value *val = dyn_cast<Value>(Ins);
              Type *ty = val->getType();
              Value *val0 = Ins->getOperand(0);
              if (ty->isPointerTy()) {
                variable[val] = "*" + variable[val0];
              }
              if (ty->isIntegerTy()) {
                variable[val] = variable[val0];
              }
            }

            if (dyn_cast<StoreInst>(Ins)) {

              // errs() << "store" << "\n";

              Value *val0 = Ins->getOperand(0);
              Value *val1 = Ins->getOperand(1);
              // =========================
              // Print assignment number
              // =========================
              std::string num_assign = "S" + std::to_string(nline);
              errs() << num_assign << "\n";

              // =========================
              // Step 1: Compute TREF(S)
              // =========================
              std::vector<std::string> ref;
              //  RHS assignment, including all the subtrees
              if (variable.find(val0) != variable.end()) {
                std::string rhs_var = variable[val0];
                if (rhs_var[0] == '*') {
                  while (rhs_var[0] == '*') {
                    ref.push_back(rhs_var);
                    rhs_var.erase(0,1);
                  }
                  ref.push_back(rhs_var);
                }
              }
              //  LHS assignment, including only proper subtrees
              if (variable.find(val1) != variable.end()) {
                std::string lhs_var = variable[val1];
                if (lhs_var[0] == '*') {
                  lhs_var.erase(0,1);
                  ref.push_back(lhs_var);
                  lhs_var.erase(0,1);
                }
              }
              // Print TREF set information
              printTSET("TREF", ref);

              // =========================
              // Step 2: Compute TGEN(S)
              // =========================
              std::vector<std::string> gen;
              gen.push_back(variable[val1]);
              // Print TGEN set information
              printTSET("TGEN", gen);

              // =========================
              // Step 2: Compute dependences
              // =========================


              // errs() << variable[val1] << " <- " << variable[val0] << "\n";
              // errs() << *ptty1 << " <- " << *ptty0 << "\n";

              nline++;
            }
          }
        }
      }
      return false;
    }

    void printTSET(std::string title, std::vector<std::string> set) {
      int size = set.size();
      if (size == 0) {
        errs() << title << ":{}\n";
      }
      else if (size == 1) {
        errs() << title << ":{" << set[0] << "}\n";
      }
      else {
        errs() << title << ":{";
        for (int i = 0; i < size - 1; i++) {
          errs() << set[i] << ",";
        }
        errs() << set[size - 1] << "}\n";
      }
    }
  };

  char Hello::ID = 0;

  //register class 
  static RegisterPass<Hello> X("hello", "Hello World Pass", false, true);
  
}