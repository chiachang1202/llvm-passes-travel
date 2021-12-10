#!/bin/bash
# Program:
#       This script execute LLVM opt operation.
# History:
# 2021/12/08 First release

opt -load inject_func_call.so -enable-new-pm=0 -inject-func-call test.ll -o /dev/null