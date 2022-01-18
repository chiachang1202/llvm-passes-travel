#include "alias_analysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

#include <algorithm>
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
    std::unordered_map<Value*, std::string> allocation;
    std::unordered_map<std::string, std::string> tdef;
    std::unordered_map<std::string, std::string> tequ;
    int nline = 0;

    //override an abstract virtual method inherited from FunctionPass. 
    virtual bool runOnModule(Module &M) {
      
      for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (Function::iterator BB = F->begin(); BB != F->end(); BB++) {

          std::vector<std::string> global_ref;

          for (BasicBlock::iterator Ins = BB->begin(); Ins != BB->end(); Ins++) {
            if (dyn_cast<AllocaInst>(Ins)) {
              // errs() << *Ins << "\n";
              Type *ty = Ins->getType();
              std::string name = Ins->getName().str();
              if (ty->isPointerTy()) {
                Type *ptty = dyn_cast<PointerType>(ty)->getElementType();
                variable[dyn_cast<Value>(Ins)] = name;
                allocation[dyn_cast<Value>(Ins)] = name;
              }
            }

            if (dyn_cast<BinaryOperator>(Ins)) {
              std::string name = Ins->getName().str();

              variable[dyn_cast<Value>(Ins)] = name;

              Value *val0 = Ins->getOperand(0);
              if (allocation.find(val0) != allocation.end()) {
                std::string para0 = variable[val0];
                global_ref.push_back(para0);
              }

              Value *val1 = Ins->getOperand(1);
              if (allocation.find(val1) != allocation.end()) {
                std::string para1 = variable[val1];
                global_ref.push_back(para1);
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
                allocation[val] = variable[val0];
              }
            }

            if (dyn_cast<StoreInst>(Ins)) {

              // errs() << "store" << "\n";

              Value *val0 = Ins->getOperand(0);
              Value *val1 = Ins->getOperand(1);
              std::string LHS, RHS;
              Type *t_LHS = dyn_cast<PointerType>(val1->getType())->getElementType(), *t_RHS = val0->getType();

              // For Debugging, make sure the variable is correctly
              if (dyn_cast<ConstantInt>(val0)) {
                ConstantInt* imme = dyn_cast<ConstantInt>(val0);
                LHS = variable[val1];
                RHS = std::to_string(imme->getSExtValue());
              }
              else {
                LHS = variable[val1];
                if (t_LHS->isPointerTy()) {        
                  RHS = "&" + variable[val0];
                }
                else {
                  RHS = variable[val0];
                }
              }

              // errs() << LHS << " <- " << RHS << "\n";
              // errs() << LHS << "[" << *t_LHS << "]" << " <- " << RHS << "[" << *t_RHS << "]" "\n";

              // =========================
              // Print assignment number
              // =========================
              std::string num_assign = "S" + std::to_string(nline+1);
              errs() << num_assign << "\n";

              // =========================
              // Step 1: Compute TREF(S)
              // =========================
              std::vector<std::string> ref;
              //  RHS assignment, including all the subtrees
              if (!dyn_cast<ConstantInt>(val0)) {
                if (allocation.find(val0) != allocation.end()) {
                  add_subtree(ref, RHS);
                }
                else {
                  ref = global_ref;
                }
              }
              //  LHS assignment, including only proper subtrees
              add_proper_subtree(ref, LHS);
              // Include co-alias
              for (auto &str : ref) {
                for (auto &pair : tequ) {
                  if (str.compare(pair.first) == 0) {
                    if (std::find(ref.begin(), ref.end(), pair.second) == ref.end()) {
                      ref.push_back(pair.second);
                    }
                  }
                  if (str.compare(pair.second) == 0) {
                    if (std::find(ref.begin(), ref.end(), pair.first) == ref.end()) {
                      ref.push_back(pair.first);
                    }
                  }
                }
              }

              // Print TREF set information
              printTSET("TREF", ref);

              // =========================
              // Step 2: Compute TGEN(S)
              // =========================
              std::vector<std::string> gen;
              gen.push_back(LHS);
              // Include co-alias
              for (auto &str : gen) {
                for (auto &pair : tequ) {
                  if (str.compare(pair.first) == 0) {
                    if (std::find(gen.begin(), gen.end(), pair.second) == gen.end()) {
                      gen.push_back(pair.second);
                    }
                  }
                  if (str.compare(pair.second) == 0) {
                    if (std::find(gen.begin(), gen.end(), pair.first) == gen.end()) {
                      gen.push_back(pair.first);
                    }
                  }
                }
              }

              // Print TGEN set information
              printTSET("TGEN", gen);

              // =========================
              // Step 3: Compute dependences
              // =========================

              errs() << "DEP: {" << "\n";
              for (auto &var : ref) {
                if (tdef.find(var) != tdef.end()) {
                  errs() << var << " :" << tdef[var] << "-------" << num_assign << "\n";
                }
              }
              for (auto &var : gen) {
                if (tdef.find(var) != tdef.end()) {
                  errs() << var << " :" << tdef[var] << "---O---" << num_assign << "\n";
                }
              }
              errs() << "}" << "\n";

              // =========================
              // Step 4: Update TDEF_i+1
              // =========================
              // Given TGEN and TDEF, remove the intersection and get the union
              
              // Direct assign unorder_map key/value pair to update/insert the TDEF
              for (auto &item : gen) {
                tdef[item] = num_assign;
              }

              std::vector<std::string> front;
              std::vector<std::string> back;
              for (auto &item : tdef) {
                front.push_back(item.first);
                back.push_back(item.second);
              }
              printT2SET("TDEF", front, back);

              // =========================
              // Step 5: Update TEQUIV_i+1
              // =========================

              // If the element in TEQUIV is the proper subtree of the TGEN, then remove it. 
              remove_proper_subtree(tequ, gen);

              if (t_LHS->isPointerTy() && t_RHS->isPointerTy()) {

                std::string reduce_LHS = reduce_variable("*" + LHS);
                std::string reduce_RHS = reduce_variable("*" + RHS);
                tequ[reduce_LHS] = reduce_RHS;
                // transitive closure
                for (auto &pair1 : tequ) {
                  std::string lhs = "*" + pair1.first;
                  std::string rhs = "*" + pair1.second;
                  for (auto &pair2 : tequ) {
                    if (pair2.first.compare(pair1.first) != 0) {
                      // A, B
                      // C, D
                      if (lhs.compare(pair2.first) == 0) {
                        tequ[rhs] = pair2.second;
                      }
                      else if (lhs.compare(pair2.second) == 0) {
                        tequ[rhs] = pair2.first;
                      }
                      else if (rhs.compare(pair2.first) == 0) {
                        tequ[lhs] = pair2.second;
                      }
                      else if (rhs.compare(pair2.first) == 0) {
                        tequ[lhs] = pair2.second;
                      }
                    }
                  }
                }
              }

              front.clear();
              back.clear();
              for (auto &item : tequ) {
                front.push_back(item.first);
                back.push_back(item.second);
              }

              printT2SET("TEQUIV", front, back);

              global_ref.clear();
              nline++;
            }
          }
        }
      }
      return false;
    }

    // To-Do: clarify the definition about "subtree" and "proper subtree"
    void add_subtree(std::vector<std::string>& set, std::string var) {
      int length = var.length();
      if (length > 1) {
        if (var[0] == '*') {
          while (var[0] == '*') {
            set.push_back(var);
            var = var.substr(1,var.length()-1);
          }
          set.push_back(var);
        }
      }
      else if (length == 1) {
        set.push_back(var);
      }
    }

    void add_proper_subtree(std::vector<std::string>& set, std::string var) {
      int length = var.length();
      if (length > 1) {
        if (var[0] == '*') {
          var = var.substr(1,var.length()-1);
          // while (var[0] == '*') {
          //   set.push_back(var);
          //   var = var.substr(1,var.length()-1);
          // }
          set.push_back(var);
        }
      }
    }

    void remove_proper_subtree(std::unordered_map<std::string, std::string>& map, std::vector<std::string> set) {
      // To-Do: modified this function
      // easy-to-do version, search from TGEN/TREF to eliminate element in TEQUIV
      for (auto &element : set) {
        std::string str = "*" + element;
        for (int i = 0; i < 4; i++) {
          for (auto &pair : map) {
            if (str.compare(pair.first) == 0 || str.compare(pair.second) == 0) {
              map.erase(map.find(pair.first));
            }
          }
          str = "*" + str;
        }
      }
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
    void printT2SET(std::string title, std::vector<std::string> front, std::vector<std::string> back) {
      int size = front.size();
      if (size == 0) {
        errs() << title << ":{}\n";
      }
      else if (size == 1) {
        errs() << title << ":{(" << front[0] << "," << back[0] << ")}\n";
      }
      else {
        errs() << title << ":{";
        for (int i = 0; i < size - 1; i++) {
          errs() << "(" << front[i] << "," << back[i] << "),";
        }
        errs() << "(" << front[size - 1] << "," << back[size - 1] << ")}\n";
      }
    }

    std::string reduce_variable(std::string var) {
      int len = var.length();
      if (len > 2) {
        if (var[0] == '*' && var[1] == '&') {
          var = var.substr(2, len - 2);
        }
      }
      return var;
    }
  };

  char Hello::ID = 0;

  //register class 
  static RegisterPass<Hello> X("hello", "Hello World Pass", false, true);
  
}