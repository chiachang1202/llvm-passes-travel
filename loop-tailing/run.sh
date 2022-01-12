#!/bin/bash
# Program:
#       This script execute LLVM opt operation.
# History:
# 2021/12/08 First release

opt -load ./LoopTailing.so -enable-new-pm=0 -S -hello test.ll -o test_opt.ll