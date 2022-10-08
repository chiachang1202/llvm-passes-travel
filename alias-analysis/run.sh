#!/bin/bash
# Program:
#       This script execute LLVM opt operation.
# History:
# 2021/12/08 First release

opt -load ./alias_analysis.so -enable-new-pm=0 -hello ./icpp2.ll -o /dev/null