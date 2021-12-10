#include "inject_func_call.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  //declare a “Hello” class that is a subclass of ModulePass. 
  struct InjectFuncCall : public ModulePass {
    //pass identifier used by LLVM to identify pass
    static char ID;
    InjectFuncCall() : ModulePass(ID) {}
    //override an abstract virtual method inherited from FunctionPass. 
    virtual bool runOnModule(Module &M) {

      LLVMContext &ctx = M.getContext();

      PointerType *printf_arg_ty = PointerType::getUnqual(Type::getInt8Ty(ctx));

      FunctionType *printf_ty = FunctionType::get(
        IntegerType::getInt32Ty(ctx),
        printf_arg_ty,
        true
      );
      
      FunctionCallee printf = M.getOrInsertFunction("printf", printf_ty);

      Function *printf_f = dyn_cast<Function>(printf.getCallee());

      printf_f->setDoesNotThrow();
      printf_f->addParamAttr(0, Attribute::NoCapture);
      printf_f->addParamAttr(0, Attribute::ReadOnly);

      Constant *printf_format_string = ConstantDataArray::getString(
        ctx, "Greeting from: %s\n number of arguments: %d\n"
      );

      Constant *printf_format_string_variable = M.getOrInsertGlobal(
        "printf_format_string_variable",
        printf_format_string->getType()
      );

      dyn_cast<GlobalVariable>(printf_format_string_variable)->setInitializer(printf_format_string);

      for (Function &F : M) {

        if (F.isDeclaration()) {
          // errs() << "Function " <<  F.getName() << " is declaration." << "\n";
          continue;
        }

        IRBuilder<> builder(&*F.getEntryBlock().getFirstInsertionPt());

        Constant *func_name = builder.CreateGlobalStringPtr(F.getName());

        Value *format_string_pointer = builder.CreatePointerCast(
          printf_format_string_variable,
          printf_arg_ty,
          "format_string"
        );

        builder.CreateCall(
          printf,
          {format_string_pointer, func_name, builder.getInt32(F.arg_size())}
        );

      }

      return true;
    }
  };

  char InjectFuncCall::ID = 0;

  //register class 
  static RegisterPass<InjectFuncCall> X("inject-func-call", "Inject `Printf` function call", false, false);
  
}