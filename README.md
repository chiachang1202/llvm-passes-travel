# llvm-passes-travel
A simple LLVM passes playground which are inspired by NTHU Advanced Compiler (CS5404)
## User Guide
### Build the repository
```sh
export LLVM_DIR=<preinstalled llvm> # Ex: /usr/local/opt/llvm
mkdir build && cd build
cmake .. -DLT_LLVM_INSTALL_DIR=$LLVM_DIR
make
```
### Generate `LLVM IR` from inputs
```sh
# Use MBASub example command as tutorial
clang -emit-llvm -S ../inputs/input_for_mba_sub.c -o input_for_mba_sub.ll
```
- `-fno-discard-value-names`: preverse the variable name in the LLVM IR.
### Run the Analysis/Transformation Pass with `opt`
```sh
# The command can only used on legacy pass
opt -load lib/libMBA.dylib -enable-new-pm=0 -mba -S input_for_mba_sub.ll -o out.ll
```
- `-enable-new-pm=0`: Use legacy pass manager with `opt`
---
## ChangeLog
### [1.0.0] - 2022-10-09
#### Added
- User Guide section in README.md
- Question section in README.md
- Question [1]
- Mixed Boolean Arithmetic (MBA) Transformation - MBASub
#### Changed
- Improve the building system from pure hand-writing Makefile to cmake - refer to [llvm-tutor](https://github.com/banach-space/llvm-tutor)
#### Removed
- Roadmap section in the README.md
---
## Question
### [1] - 2022-10-09 - ReplaceInstWithInst and iterate BB weird behavior
- The `llvm::ReplaceInstWithInst (BasicBlock::InstListType &BIL, BasicBlock::iterator &BI, Instruction *I)` can't used in **Range-based for loop**
- `llvm::ReplaceInstWithInst (Instruction *From, Instruction *To)` can't used.
---
## References
#### LLVM Passes
- Writing an LLVM Pass: 101, A. Warzynski, LLVM Developers’ Meeting 2019, [slides](https://llvm.org/devmtg/2019-10/slides/Warzynski-WritingAnLLVMPass.pdf), [video](https://youtu.be/ar7cJl2aBuU), [github](https://github.com/banach-space/llvm-tutor)
- Building, Testing and Debugging a Simple out-of-tree LLVM Pass, S. Guelton & A. Guinet, LLVM Developers’ Meeting 2015, [slides](https://llvm.org/devmtg/2015-10/slides/GueltonGuinet-BuildingTestingDebuggingASimpleOutOfTreePass.pdf), [video](https://youtu.be/BnlG-owSVTk), [github](https://github.com/quarkslab/llvm-dev-meeting-tutorial-2015)

#### LLVM Developers’ Meeting Slides
- 2019 Slides [slides](https://llvm.org/devmtg/2019-10/slides/)

#### Clang Overview
- An overview of Clang, S. Haastregt & A. Stulova, LLVM Developers’ Meeting 2019, [slides](https://llvm.org/devmtg/2019-10/slides/ClangTutorial-Stulova-vanHaastregt.pdf), [video](https://youtu.be/5kkMpJpIGYU)

#### Compiler Online Course
- CMU Lectures [slides](https://www.cs.cmu.edu/afs/cs/academic/class/15745-s16/www/lectures/)
- Northwestern University Alias Analysis [slides](https://users.cs.northwestern.edu/~simonec/files/Teaching/CAT/slides/AliasAnalysis.pdf)

#### LLVM Backend
- Tutorial: Creating a LLVM Backend for the cpu0 Architecture, Chen Chung-Shu [slides](http://jonathan2251.github.io/lbd/TutorialLLVMBackendCpu0.pdf)
