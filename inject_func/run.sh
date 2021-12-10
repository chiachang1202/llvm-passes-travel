#!/bin/bash
# Program:
#       This script execute LLVM opt operation.
# History:
# 2021/12/08 First release

opt -load ./inject_func_call.so -inject-func-call test.ll -o test_opt.bin