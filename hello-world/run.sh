#!/bin/bash
# Program:
#       This script execute LLVM opt operation.
# History:
# 2021/12/08 First release

opt -load ./hw1.so -enable-new-pm=0 -hello ./test.ll -o /dev/null